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
		Level = LevelStruct::CreateBasicLevelStruct();
		Level.GameModeOwner = this;

		PlayerController = PlayerTankController(Level.PlayerTank, this);
		AIController = AITankController(Level.PlayerTank, Level.LevelPhoenix, this);

		SystemCollisionInstance = SystemCollision::Instance();
		SystemRenderInstance = SystemRender::Instance();
		SystemTickInstance = SystemTick::Instance();

		RestartTimer = RESTART_TIME;
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

	void Restart()
	{
		bGameIsOver = false;
		Level.DestroyLevel(true);
		Level = LevelStruct::CreateBasicLevelStruct();
		Level.GameModeOwner = this;
		Level.InitializeLevel();
		PlayerController.PlayerTank = Level.PlayerTank;
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
			RestartTimer -= DeltaTime;

			if (RestartTimer <= 0)
			{
				RestartTimer = RESTART_TIME;

				Restart();
			}
		}

		SystemCollision::CheckCollisionsAllBlock();
		SystemTick::Tick(DeltaTime);

		AIController.onTick(DeltaTime);
		
		HandleWinLooseCondition();
	}

	void Render()
	{
		SystemRender::Render();
	}

	bool bGameIsOver = false;
	bool bIsGameOverWin = false;

	int RestartTimer;

	LevelStruct Level;
	AITankController AIController;
	PlayerTankController PlayerController;

	SystemCollision SystemCollisionInstance;
	SystemRender SystemRenderInstance;
	SystemTick SystemTickInstance;

	Tank* GetPlayerTank() { return Level.PlayerTank; }
	TankSpawner* GetTankSpawner() { return Level.LevelEnemyTankSpawner; }
	Phoenix* GetPhoenix() { return Level.LevelPhoenix; }
};