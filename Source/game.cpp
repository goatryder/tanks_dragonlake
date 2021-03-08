#include "Framework.h"

#include "GlobalConstants.h"

#include "Systems/SystemRender.h"
#include "Systems/SystemTick.h"
#include "Systems/SystemCollision.h"

#include "Entities/SpriteEntity.h"
#include "GameObjects/Tank.h"
#include "GameObjects/BrickBlock.h"
#include "GameObjects/TankSpawner.h"

#include "Helpers/DebugPrint.h"


/* Test Framework realization */
class MyFramework : public Framework {

// initialization  ////////////////////////////////////////////////////////////////////////////////////////////////////

public:
	virtual const char* GetTitle() override
	{
		return "Tanki";
	}

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = WINDOW_W;
		height = WINDOW_H;
		fullscreen = false;
	}

	Tank* TankTest = nullptr;

	virtual bool Init() 
	{
		// BG
		SpriteEntity::SpawnBasicSprite(BG_IMAGE_PATH, VecInt2D(0, 0));

		// Brick
		//BrickBlock::SpawnBrickBlockSolid(VecInt2D(GAME_AREA_W0 + 32, GAME_AREA_H0));
		BrickBlock::SpawnBrickBlockSolid(VecInt2D(GAME_AREA_W0 + 32, GAME_AREA_H0 + 64));
		//BrickBlock::SpawnBrickBlockSolid(VecInt2D(GAME_AREA_W1 - 32, GAME_AREA_H0));
		BrickBlock::SpawnBrickBlockSolid(VecInt2D(GAME_AREA_W1 - 64, GAME_AREA_H0));
		BrickBlock::SpawnBrickBlockSolid(VecInt2D(GAME_AREA_W1 - 64, GAME_AREA_H1 - 64));
		BrickBlock::SpawnBrickBlockSolid(VecInt2D(GAME_AREA_W1 - 64, GAME_AREA_H1 - 96));
		BrickBlock::SpawnBrickBlockSolid(VecInt2D(GAME_AREA_MID_W, GAME_AREA_H1 - 96));
		BrickBlock::SpawnBrickBlockSolid(VecInt2D(GAME_AREA_MID_W - 32, GAME_AREA_H1 - 96));

		BrickBlock::SpawnBrickBlockSolid(VecInt2D(GAME_AREA_W0 + 64, GAME_AREA_H1 - 128));
		BrickBlock::SpawnBrickBlockSolid(VecInt2D(GAME_AREA_W0 + 128, GAME_AREA_H1 - 128));
		
		// Enemy tank spawner
		TankSpawner::CreateBasicTankSpawnerCorners(true);

		// Tank
		TankTest = Tank::SpawnTankBasic(VecInt2D(GAME_AREA_MID_W + 64, GAME_AREA_MID_H + 64), Direction::UP);

		return true;
	}

	virtual void Close() 
	{

	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// game logic runner tick  ////////////////////////////////////////////////////////////////////////////////////////////

private:
	// tick time
	unsigned int TimeSinceLastTick = 0;
	unsigned int TickDeltaTime = 0;

	inline void SetTickDeltaTime()
	{
		unsigned int TickCount = getTickCount();
		TickDeltaTime = TickCount - TimeSinceLastTick;
		TimeSinceLastTick = TickCount;
	}

	// game logic tick gate
	unsigned int GameLogicTickAccomulation = GAME_LOGIC_TICK;

	inline bool IsGameLogicTickGateOpen()
	{
		GameLogicTickAccomulation += TickDeltaTime;
		
		if (GameLogicTickAccomulation >= GAME_LOGIC_TICK)
		{
			GameLogicTickAccomulation = 0;
			return true;
		}
		else
		{
			return false;
		}
	}

	// tick functions
	inline void GameLogicTick()
	{
		SystemCollision::CheckCollisionsAllBlock();
		SystemTick::Tick(GAME_LOGIC_TICK);
	}

	inline void RenderTick()
	{
		SystemRender::Render();
	}

public:
	// get delta tick time
	inline unsigned int GetTickDeltaTime() const
	{
		return TickDeltaTime;
	}

	// tick logic runner
	virtual bool Tick() 
	{
		SetTickDeltaTime();

		if (IsGameLogicTickGateOpen()) GameLogicTick();
		
		RenderTick();
		
		return false;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Input handlers  ////////////////////////////////////////////////////////////////////////////////////////////////////

public:

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) 
	{

	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) 
	{
		if (button == FRMouseButton::LEFT && !isReleased && TankTest != nullptr)
		{
			TankTest->Fire();
		}
	}

	virtual void onKeyPressed(FRKey k) 
	{
		if (k == FRKey::RIGHT)
		{
			// PRINT(PrintColor::Yellow, "Pressed RIGHT");
			
			if (TankTest != nullptr)
			{
				TankTest->MoveBegin(Direction::RIGHT);
			}
		}
		else if (k == FRKey::LEFT)
		{
			// PRINT(PrintColor::Yellow, "Pressed LEFT");

			if (TankTest != nullptr)
			{
				TankTest->MoveBegin(Direction::LEFT);
			}
		}
		else if (k == FRKey::UP)
		{
			// PRINT(PrintColor::Yellow, "Pressed UP");

			if (TankTest != nullptr)
			{
				TankTest->MoveBegin(Direction::UP);
			}
		}
		else
		{
			// PRINT(PrintColor::Yellow, "Pressed DOWN");

			if (TankTest != nullptr)
			{
				TankTest->MoveBegin(Direction::DOWN);
			}
		}
	}

	virtual void onKeyReleased(FRKey k) 
	{
		if (k == FRKey::RIGHT)
		{
			// PRINT(PrintColor::Yellow, "Released RIGHT");

			if (TankTest != nullptr)
			{
				TankTest->MoveEnd(Direction::RIGHT);
			}
		}
		else if (k == FRKey::LEFT)
		{
			// PRINT(PrintColor::Yellow, "Released LEFT");

			if (TankTest != nullptr)
			{
				TankTest->MoveEnd(Direction::LEFT);
			}
		}
		else if (k == FRKey::UP)
		{
			// PRINT(PrintColor::Yellow, "Released UP");

			if (TankTest != nullptr)
			{
				TankTest->MoveEnd(Direction::UP);
			}
		}
		else
		{
			// PRINT(PrintColor::Yellow, "Released DOWN");

			if (TankTest != nullptr)
			{
				TankTest->MoveEnd(Direction::DOWN);
			}

		}
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

};

int main(int argc, char *argv[])
{
	return run(new MyFramework);
}
