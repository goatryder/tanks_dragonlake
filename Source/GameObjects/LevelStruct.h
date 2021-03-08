#pragma once

#include <vector>
#include "../Entities/SpriteEntity.h"
#include "BrickBlock.h"
#include "Tank.h"
#include "TankSpawner.h"
#include "Phoenix.h"

struct LevelStruct
{
public:
	LevelStruct() {}
	LevelStruct(Tank* PlayerTank, Phoenix* LevelPhoenix, TankSpawner* LevelTankSpawner, std::vector<RenderBase*> RenderQueue)
		: PlayerTank(PlayerTank), LevelPhoenix(LevelPhoenix), LevelTankSpawner(LevelTankSpawner), RenderQueue(RenderQueue) {}
	
	Tank* PlayerTank = nullptr;
	Phoenix* LevelPhoenix = nullptr;
	TankSpawner* LevelTankSpawner = nullptr;

	/** RenderQueue, store RenderBase instanses here, PlayerTank, LevelPhoenix, LevelTanksSpawner should not be there */
	std::vector<RenderBase*> RenderQueue = {};

	/** call Initialize() for all RenderObj in RenderQueue, then for PlayerTank, LevelPhoenix, LeverTankSpawner */
	void InitializeLevel()
	{
		for (auto& RenderBaseInstance : RenderQueue)
		{
			if (RenderBaseInstance != nullptr)
			{
				RenderBaseInstance->Initialize();
			}
		}

		PlayerTank->Initialize();
		LevelPhoenix->Initialize();
		LevelTankSpawner->Initialize();
	}

	/** call Destroy() for all RenderObj in RenderQueue, then for PlayerTank, LevelPhoenix, LeverTankSpawner 
	  * bForce, clear SystemTick, SystemCollision, SystemRender after Destroy();
	  */
	void DestroyLevel(bool bForce = false)
	{
		for (auto& RenderBaseInstance : RenderQueue)
		{
			if (RenderBaseInstance != nullptr)
			{
				RenderBaseInstance->Destroy();
			}
		}

		PlayerTank->Destroy();
		LevelPhoenix->Destroy();
		LevelTankSpawner->Destroy();

		if (bForce)
		{
			SystemRender::ClearRenderQueue();
			SystemCollision::ClearCheckCollisionSet();
			SystemTick::ClearTickQueue();
		}
	}

	static LevelStruct BasicLevel;
};