#include "LevelStruct.h"

LevelStruct CreateBasicLevelStruct()
{
	VecInt2D ChunkZero(GAME_AREA_OFFSET_W, GAME_AREA_OFFSET_H);
	VecInt2D ChunkOffset(GAME_CHUNK_W, GAME_CHUNK_H);
	VecInt2D ChunkOffset_X(GAME_CHUNK_W, 0);
	VecInt2D ChunkOffset_Y(0, GAME_CHUNK_H);

	VecInt2D ChunkLastOffset_X(GAME_AREA_H1, 0);
	VecInt2D ChunkLastOffset_Y(0, GAME_AREA_W1);

	VecInt2D BasePosition(GAME_AREA_MID_W, GAME_AREA_H1);

	VecInt2D PlayerSpawnPosition = BasePosition - ChunkOffset * 2;

	Tank* PlayerTank = Tank::SpawnTankBasic(PlayerSpawnPosition, Direction::UP);

	Phoenix* PhoenixBase = Phoenix::SpawnPhoenix(BasePosition, Anchor::BOTTOM);

	TankSpawner* TankSpawner = TankSpawner::CreateBasicTankSpawnerCorners();

	SpriteEntity* BG = SpriteEntity::SpawnBasicSprite(BG_IMAGE_PATH, VecZero);

	std::vector<RenderBase*> RenderQueue = { 
		
		BG,
		/*
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


		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset_Y * 6),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset_Y * 6 + ChunkOffset_X * 2),
		BrickBlock::SpawnBrickBlockSolid(ChunkZero + ChunkOffset_Y * 6 + ChunkOffset_X * 3),

		BrickBlock::SpawnBrickBlockSolid(-ChunkZero - ChunkOffset_Y * 6 + ChunkLastOffset_X),
		BrickBlock::SpawnBrickBlockSolid(-ChunkZero - ChunkOffset_Y * 6 - ChunkOffset_X * 2 + ChunkLastOffset_X),
		BrickBlock::SpawnBrickBlockSolid(-ChunkZero - ChunkOffset_Y * 6 - ChunkOffset_X * 3 + ChunkLastOffset_X)
		*/
	};

	return LevelStruct(PlayerTank, PhoenixBase, TankSpawner, RenderQueue);
}

LevelStruct LevelStruct::BasicLevel = CreateBasicLevelStruct();