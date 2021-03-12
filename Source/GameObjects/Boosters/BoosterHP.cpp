#include "BoosterHP.h"

#include "../LevelStruct.h"
#include "../Tank.h"
#include "../../Entities/SpriteEntity.h"
#include "../../Helpers/DebugPrint.h"

void BoosterHP::Activate(LevelStruct* Level, Tank* BoostedTank)
{
	int NewRespawnNum = Level->PlayerRespawnNum + ExtraLifeVal;

	if (NewRespawnNum > Level->PlayerRespawnNumMax)
	{
		Level->PlayerRespawnNum = Level->PlayerRespawnNumMax;
	}
	else
	{
		Level->PlayerRespawnNum = NewRespawnNum;
	}
	
	PRINTF(PrintColor::White, "%s Picked Extra Life for Player: %d", BoostedTank->GetName(), Level->PlayerRespawnNum);
}

BoosterHP* BoosterHP::SpawnPlayerHPBooster(LevelStruct* Level, VecInt2D Position)
{
	SpriteEntity* BoosterSprite = new SpriteEntity(BOOST_HP);
	BoosterHP* SpawnedBooster = new BoosterHP(BoosterSprite, Position);
	
	SpawnedBooster->SetLevel(Level);
	SpawnedBooster->ExtraLifeVal = HP_BOOSTER_VAL;

	// add player tank to collision white list
	Tank* PlayerTank = Level->PlayerTank;
	
	if (PlayerTank != nullptr)
	{
		SpawnedBooster->bCollisionFilterIsWhiteList = true;
		SpawnedBooster->AddToCollisionFilter(PlayerTank);
	}

	SpawnedBooster->Initialize();

	return SpawnedBooster;
}
