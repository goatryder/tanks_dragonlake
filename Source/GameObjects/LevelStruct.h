#pragma once

#include "Tank.h"
#include "TankSpawner.h"
#include "Phoenix.h"

class GameMode;

struct LevelStruct
{
public:
	LevelStruct() {}
	LevelStruct(TankSpawnPoint PlayerSpawnPoint, int PlayerRespawnNum, Tank* PlayerTank, 
		int SpawnEnemyTankNum, TankSpawner* LevelEnemyTankSpawner, 
		Phoenix* LevelPhoenix,  std::list<RenderBase*> RenderQueue)
		: PlayerSpawnPoint(PlayerSpawnPoint), PlayerRespawnNum(PlayerRespawnNum), PlayerTank(PlayerTank),
		EnemyTankKillLeft(SpawnEnemyTankNum), LevelEnemyTankSpawner(LevelEnemyTankSpawner), 
		LevelPhoenix(LevelPhoenix),  RenderQueue(RenderQueue) {}

	GameMode* GameModeOwner = nullptr;

	TankSpawnPoint PlayerSpawnPoint;
	int PlayerRespawnNum = 1;
	Tank* PlayerTank = nullptr;
	
	bool bBaseIsDestroyed = false;
	Phoenix* LevelPhoenix = nullptr;

	int EnemyTankKillLeft = 20;
	TankSpawner* LevelEnemyTankSpawner = nullptr;

	/** RenderQueue, store RenderBase instanses here, PlayerTank, LevelPhoenix, LevelTanksSpawner should not be there */
	std::list<RenderBase*> RenderQueue = {};

	/** call Initialize() for all RenderObj in RenderQueue, then for PlayerTank, LevelPhoenix, LeverTankSpawner */
	void InitializeLevel()
	{
		for (auto& RenderBaseInstance : RenderQueue)
		{
			if (RenderBaseInstance != nullptr)
			{
				RenderBaseInstance->Initialize();
				RenderBaseInstance->SetLevel(this);
			}
		}

		if (PlayerTank != nullptr)
		{
			PlayerTank->Initialize();
			PlayerTank->SetLevel(this);
		}

		if (LevelPhoenix != nullptr)
		{
			LevelPhoenix->Initialize();
			LevelPhoenix->SetLevel(this);
		}

		if (LevelEnemyTankSpawner != nullptr)
		{
			LevelEnemyTankSpawner->Initialize();
			LevelEnemyTankSpawner->SetLevel(this);
		}
	}

	/** Clear Render Collision Tick Containers */
	void DestroyLevel(bool bForceDestroy = false)
	{
		for (auto& RenderInstance : RenderQueue)
		{
			RenderInstance->Destroy();
		}

		SystemRender::ClearRenderQueue(bForceDestroy);
		SystemCollision::ClearCheckCollisionSet(bForceDestroy);
		SystemTick::ClearTickQueue(bForceDestroy);
	}

	void RemoveFromLevel(RenderBase* LevelObj)
	{
		std::list<RenderBase*>::iterator Iter;
		Iter = std::find(RenderQueue.begin(), RenderQueue.end(), LevelObj);

		if (Iter != RenderQueue.end())
		{
			RenderQueue.erase(Iter);
		}
	}

	static LevelStruct BasicLevel;
};