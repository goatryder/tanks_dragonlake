#pragma once

#include "GameObjects/LevelStruct.h"
#include "AITankController.h"
#include "PlayerTankController.h"


/** Basic game-loop handler */
class GameMode
{
public:
	
	GameMode()
	{
		Level = LevelStruct::BasicLevel;
		Level.GameModeOwner = this;

		PlayerController = PlayerTankController(Level.PlayerTank, this);
		AIControlller = AITankController(Level.PlayerTank, Level.LevelPhoenix, this);

		SystemCollisionInstance = SystemCollision::Instance();
		SystemRenderInstance = SystemRender::Instance();
		SystemTickInstance = SystemTick::Instance();
	}

	~GameMode() {}

	void Initialize()
	{
		Level.InitializeLevel();
	}

	void Finalize()
	{
		Level.DestroyLevel();
	}

	void HandleWinLooseCondition()
	{
		if (Level.bBaseIsDestroyed || Level.PlayerRespawnNum <= -1)
		{
			bGameIsOver = true;
			bIsGameOverWin = false;
		}
		else if (Level.EnemyTankKillLeft <= 0)
		{
			bGameIsOver = true;
			bIsGameOverWin = true;
		}
	}

	void Tick(unsigned int DeltaTime)
	{
		if (bGameIsOver)  // win loose sprites
		{
			return;
		}

		SystemCollision::CheckCollisionsAllBlock();
		SystemTick::Tick(DeltaTime);

		AIControlller.onTick(DeltaTime);
		
		HandleWinLooseCondition();
	}

	void Render()
	{
		SystemRender::Render();
	}

	bool bGameIsOver = false;
	bool bIsGameOverWin = false;

	LevelStruct Level;
	AITankController AIControlller;
	PlayerTankController PlayerController;

	SystemCollision SystemCollisionInstance;
	SystemRender SystemRenderInstance;
	SystemTick SystemTickInstance;

	Tank* GetPlayerTank() { return Level.PlayerTank; }
	TankSpawner* GetTankSpawner() { return Level.LevelEnemyTankSpawner; }
	Phoenix* GetPhoenix() { return Level.LevelPhoenix; }
};