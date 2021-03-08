#include "TankSpawner.h"
#include "../Helpers/DebugPrint.h"
#include "Tank.h"
#include "GlobalConstants.h"

TankSpawnPoint TankSpawnPoint::BottomLeftSpawnPoint(VecInt2D(GAME_AREA_W0, GAME_AREA_H1), Direction::UP, Anchor::BOTTOM_LEFT);
TankSpawnPoint TankSpawnPoint::BottomRightSpawnPoint(VecInt2D(GAME_AREA_W1, GAME_AREA_H1), Direction::UP, Anchor::BOTTOM_RIGHT);
TankSpawnPoint TankSpawnPoint::TopLeftSpawnPoint(VecInt2D(GAME_AREA_W0, GAME_AREA_H0), Direction::DOWN, Anchor::TOP_LEFT);
TankSpawnPoint TankSpawnPoint::TopRightSpawnPoint(VecInt2D(GAME_AREA_W1, GAME_AREA_H0), Direction::DOWN, Anchor::TOP_RIGHT);

int TankSpawner::SpawnerCount = 0;


TankSpawner::TankSpawner(std::vector<TankSpawnPoint> SpawnPoints, int TankSpawnNumMax, unsigned int SpawnRate)
	: SpawnPoints(SpawnPoints), TankSpawnNumMax(TankSpawnNumMax), SpawnRate(SpawnRate)
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

TankSpawnPoint& TankSpawner::ChooseSpawnPoint()
{
	int RandomIndex = rand() % SpawnPoints.size();
	TankSpawnPoint& SpawnPoint = SpawnPoints[RandomIndex];
	return SpawnPoint;
}

void TankSpawner::SpawnTank(TankSpawnPoint& SpawnPoint)
{
	Tank::SpawnEnemyTankBasic(SpawnPoint.SpawnPosition, SpawnPoint.SpawnDirection, SpawnPoint.SpawnAnchor, true);

	TankSpawnNum++;

	if (TankSpawnNum >= TankSpawnNumMax)
	{
		Destroy();
	}
}

TankSpawner* TankSpawner::CreateBasicTankSpawnerCorners(bool bInitialize)
{
	std::vector<TankSpawnPoint> CornerSpawnPoints = {
		TankSpawnPoint::TopLeftSpawnPoint,
		TankSpawnPoint::TopRightSpawnPoint,
		TankSpawnPoint::BottomLeftSpawnPoint,
		TankSpawnPoint::BottomRightSpawnPoint
	};

	TankSpawner* Spawner = new TankSpawner(CornerSpawnPoints, TANK_SPAWN_NUM_DEFAULT, TANK_SPAWN_RATE_DEFAULT);

	std::string Name = "tank_spawner_" + std::to_string(SpawnerCount);
	Spawner->SetName(Name);

	if (bInitialize)
	{
		Spawner->Initialize();
	}

	return Spawner;
}