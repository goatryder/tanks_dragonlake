#pragma once

#include "GameObjects/LevelStruct.h"
#include "AITankController.h"
#include "PlayerTankController.h"

#include "ObjectsUI/HUD.h"

#include "ObjectsUI/BasicUIElement.h"
#include "ObjectsUI/CountNumUI.h"
#include "ObjectsUI/CountSpriteUI.h"

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

		HUD = DefaultHUD::CreateDefaultHUD();
		HUD->GameModeOwner = this;
	}

	~GameMode() {}

	void Initialize()
	{
		HUD->InitializeHUD();
		Level.InitializeLevel();
	}

	void Finalize()
	{
		HUD->DestroyHUD();
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

	void HandleWinLooseCondition(unsigned int DeltaTime)
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
		else
		{
			return;
		}

		// restart

		RestartTimer -= DeltaTime;

		if (RestartTimer <= 0)
		{
			RestartTimer = RESTART_TIME;

			Restart();
		}
	}

	void Tick(unsigned int DeltaTime)
	{
		SystemCollision::CheckCollisionsAllBlock();

		SystemTick::Tick(DeltaTime);

		AIController.onTick(DeltaTime);

		HUD->TickHUD(DeltaTime);

		HandleWinLooseCondition(DeltaTime);
	}

	void Render()
	{
		SystemRender::Render();
		HUD->RenderHUD();
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

	// ui
	DefaultHUD* HUD = nullptr;
};