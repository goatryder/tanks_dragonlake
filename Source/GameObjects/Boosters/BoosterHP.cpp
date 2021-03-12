#include "BoosterHP.h"

#include "../LevelStruct.h"
#include "../Tank.h"
#include "../../Entities/SpriteEntity.h"
#include "../../Helpers/DebugPrint.h"

void BoosterHP::Activate(LevelStruct* Level, Tank* BoostedTank)
{
	Level->PlayerRespawnNum += ExtraLifeVal;
	
	PRINTF(PrintColor::White, "%s Recieved Extra Life: %d", BoostedTank->GetName(), Level->PlayerRespawnNum);
}

BoosterHP* BoosterHP::SpawnHPBooster(VecInt2D Position)
{
	//BoosterHP* SpawnedBooster = SpawnBooster<BoosterHP>(BOOST_HP, Position);
	
	SpriteEntity* BoosterSprite = new SpriteEntity(BOOST_HP);
	BoosterHP* SpawnedBooster = new BoosterHP(BoosterSprite, Position);
	
	SpawnedBooster->ExtraLifeVal = HP_BOOSTER_VAL;
	SpawnedBooster->Initialize();

	return SpawnedBooster;
}
