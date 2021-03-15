#include "TankSpawner.h"
#include "../Helpers/DebugPrint.h"
#include "Tank.h"
#include "GlobalConstants.h"

#include "LevelStruct.h"

int TankSpawner::SpawnerCount = 0;


TankSpawner::TankSpawner(std::vector<TankSpawnPoint> SpawnPoints, int TankSpawnNumMax, unsigned int SpawnRate, std::vector<int>FlashyTankNums)
	: SpawnPoints(SpawnPoints), TankSpawnNumMax(TankSpawnNumMax), SpawnRate(SpawnRate), FlashyTankNums(FlashyTankNums)
{
	SpawnRateAccomulated = 0;
	TankSpawnNum = 0;
}

TankSpawner::~TankSpawner()
{
}

void TankSpawner::Destroy()
{
	DisableTick();

	LevelStruct* LevelOwner = GetLevel();
	if (LevelOwner != nullptr)
	{
		LevelOwner->LevelEnemyTankSpawner = nullptr;
	}
	RenderBase::Destroy();
	 
	PRINTF(PrintColor::Red, "delete %s", GetName());

	delete this;
}

void TankSpawner::onTick(unsigned int DeltaTime)
{
	SpawnRateAccomulated += DeltaTime;

	if (SpawnRateAccomulated >= SpawnRate)
	{
		SpawnRateAccomulated = 0;

		TankSpawnPoint SpawnPoint = ChooseSpawnPoint();
		SpawnTank(SpawnPoint);
	}
}

void TankSpawner::onRender()
{
}

void TankSpawner::Initialize()
{
	EnableTick();
}

// @ToDo: spawn collision handle
TankSpawnPoint& TankSpawner::ChooseSpawnPoint()
{
	int RandomIndex = rand() % SpawnPoints.size();
	TankSpawnPoint& SpawnPoint = SpawnPoints[RandomIndex];
	return SpawnPoint;
}

void TankSpawner::SpawnTank(TankSpawnPoint& SpawnPoint)
{
	if (TankSpawnerExhausted())
	{
		Destroy();
	}
	else
	{
		Tank* SpawnedTank = Tank::SpawnEnemyTankBasic(SpawnPoint, false);
		SpawnedTank->SetLevel(GetLevel());
		
		// check flashy tank
		for (int& FlashyIndex : FlashyTankNums)
		{
			if (TankSpawnNum == FlashyIndex)
			{
				SpawnedTank->bDropPickableOnDeath = true;
				break;
			}
		}
		
		SpawnedTank->Initialize();
		
		TankSpawnNum++;
	}
};

TankSpawner* TankSpawner::SpawnBasicTankSpawnerCorners(int SpawnTankNum, int SpawnRate, const int* FlashyIndexesArr,
	int FlashyIndexesArrSize, bool bInitialize)
{
	std::vector<TankSpawnPoint> CornerSpawnPoints = {
		TankSpawnPoint::TopLeftSpawnPoint,
		TankSpawnPoint::TopRightSpawnPoint,
		TankSpawnPoint::BottomLeftSpawnPoint,
		TankSpawnPoint::BottomRightSpawnPoint
	};

	std::vector<int> FlashyIndexesVec(FlashyIndexesArr, FlashyIndexesArr + FlashyIndexesArrSize);

	TankSpawner* Spawner = new TankSpawner(CornerSpawnPoints, SpawnTankNum, SpawnRate, FlashyIndexesVec);

	std::string Name = "tank_spawner_" + std::to_string(SpawnerCount);
	Spawner->SetName(Name);

	SpawnerCount++;

	if (bInitialize)
	{
		Spawner->Initialize();
	}

	return Spawner;
}

TankSpawner* TankSpawner::SpawnBasicTankSpawnerTop(int SpawnTankNum, int SpawnRate, const int* FlashyIndexesArr, 
	int FlashyIndexesArrSize, bool bInitialize)
{
	std::vector<TankSpawnPoint> CornerSpawnPoints = {
		TankSpawnPoint::TopLeftSpawnPoint,
		TankSpawnPoint::TopRightSpawnPoint,
		TankSpawnPoint::TopCenterSpawnPoint
	};

	std::vector<int> FlashyIndexesVec(FlashyIndexesArr, FlashyIndexesArr + FlashyIndexesArrSize);

	TankSpawner* Spawner = new TankSpawner(CornerSpawnPoints, SpawnTankNum, SpawnRate, FlashyIndexesVec);

	std::string Name = "tank_spawner_" + std::to_string(SpawnerCount);
	Spawner->SetName(Name);

	SpawnerCount++;

	if (bInitialize)
	{
		Spawner->Initialize();
	}

	return Spawner;
}