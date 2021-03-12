#include "LevelStruct.h"

#include "../Entities/SpriteEntity.h"
#include "BrickBlock.h"

LevelStruct LevelStruct::CreateBasicLevelStruct()
{
	VecInt2D ChunkZero(GAME_AREA_OFFSET_W, GAME_AREA_OFFSET_H);
	VecInt2D ChunkOffset(GAME_CHUNK_W, GAME_CHUNK_H);
	VecInt2D ChunkOffset_X(GAME_CHUNK_W, 0);
	VecInt2D ChunkOffset_Y(0, GAME_CHUNK_H);

	VecInt2D ChunkLastOffset_X(GAME_AREA_H1, 0);
	VecInt2D ChunkLastOffset_Y(0, GAME_AREA_W1);

	VecInt2D BasePosition(GAME_AREA_MID_W, GAME_AREA_H1);

	TankSpawnPoint PlayerSpawnPoint(BasePosition - ChunkOffset_X * 2, Direction::UP, Anchor::BOTTOM);
	//TankSpawnPoint PlayerSpawnPoint(ChunkLastOffset_X + ChunkOffset_Y * 4, Direction::UP, Anchor::TOP_LEFT);

	Tank* PlayerTank = Tank::SpawnTankBasic(PlayerSpawnPoint);

	Phoenix* PhoenixBase = Phoenix::SpawnPhoenix(BasePosition, Anchor::BOTTOM);

	int EnemyTankSpawnNum = TANK_SPAWN_NUM_DEFAULT;

	TankSpawner* TankSpawner = TankSpawner::SpawnBasicTankSpawnerTop(EnemyTankSpawnNum, 
		TANK_SPAWN_RATE_DEFAULT, FLASHY_ARRAY_DEFAULT, FLASHY_ARRAY_DEFAULT_SIZE);

	SpriteEntity* BG = SpriteEntity::SpawnBasicSprite(BG_IMAGE_PATH, VecZero);

	BG->SetName("BackGround");

	std::list<RenderBase*> RenderQueue = {
		
		BG,
		
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 0),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 1),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 2),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 3),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 4),

		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 0),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 1),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 2),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 3),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 4),


		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 4 + ChunkOffset_Y * 0),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 4 + ChunkOffset_Y * 1),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 4 + ChunkOffset_Y * 2),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 4 + ChunkOffset_Y * 3),

		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 6 + ChunkOffset_Y * 0),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 6 + ChunkOffset_Y * 1),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 6 + ChunkOffset_Y * 2),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 6 + ChunkOffset_Y * 3),


		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 0),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 1),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 2),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 3),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 4),

		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 0),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 1),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 2),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 3),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 4),


		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset_Y * 7),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset_Y * 7 + ChunkOffset_X * 2),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset_Y * 7 + ChunkOffset_X * 3),
		
		BrickBlock::SpawnBrickBlockSolid(ChunkOffset_Y * 8 + ChunkLastOffset_X),
		BrickBlock::SpawnBrickBlockSolid(ChunkOffset_Y * 8 - ChunkOffset_X * 2 + ChunkLastOffset_X),
		BrickBlock::SpawnBrickBlockSolid(ChunkOffset_Y * 8 - ChunkOffset_X * 3 + ChunkLastOffset_X),

		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset_Y * 6 + ChunkOffset_X * 5),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset_Y * 6 + ChunkOffset_X * 7),

		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset_Y * 8 + ChunkOffset_X * 5),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset_Y * 8 + ChunkOffset_X * 7),

		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset_Y * 9 + ChunkOffset_X * 5),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset_Y * 9 + ChunkOffset_X * 7),

		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset_Y * 8 + ChunkOffset_X * 6),

		// around base
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset_Y * 11 + ChunkOffset_X * 7),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset_Y * 11 + ChunkOffset_X * 6),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset_Y * 11 + ChunkOffset_X * 5),

		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset_Y * 12 + ChunkOffset_X * 7),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset_Y * 12 + ChunkOffset_X * 5),
		//

		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 8),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 9),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 10),

		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 8),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 9),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 10),

		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 8),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 9),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 10),

		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 8),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 9),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 10),
	};

	return LevelStruct(
		PlayerSpawnPoint, PLAYER_TANK_RESPAWN_NUM, PlayerTank, 
		EnemyTankSpawnNum, TankSpawner, 
		PhoenixBase, RenderQueue);
}
