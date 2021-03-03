#include "Framework.h"

#include "GlobalConstants.h"

#include "Systems/SystemRender.h"
#include "Systems/SystemTick.h"

#include "Entities/SpriteFlipFlop.h"
#include "GameObjects/Tank.h"

#include "Helpers/DebugPrint.h"

// @ToDo: Test remove obj from systemTick, spriteManager

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
		SystemRender::CreateSprite<SpriteEntity>(BG_IMAGE_PATH);

		// Tank
		SpriteFlipFlop* Left = new SpriteFlipFlop(TANK_LEFT_0, TANK_LEFT_1);
		SpriteFlipFlop* Right = new SpriteFlipFlop(TANK_RIGHT_0, TANK_RIGHT_1);
		SpriteFlipFlop* Up = new SpriteFlipFlop(TANK_UP_0, TANK_UP_1);
		SpriteFlipFlop* Down = new SpriteFlipFlop(TANK_DOWN_0, TANK_DOWN_1);

		TankTest = new Tank(Left, Right, Up, Down);
		TankTest->SetPosition(VecInt2D(GAME_AREA_MID_W, GAME_AREA_MID_H) - TankTest->GetSize() / 2);

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

	unsigned int TestActionTimeAccomulation = 0;

	// tick functions
	inline void GameLogicTick() // execution limited to GlobalConstants.h -> MAX_GAME_TICK_RATE
	{
		SystemTick::Tick(GAME_LOGIC_TICK);

		// debug, remove
		TestActionTimeAccomulation += GAME_LOGIC_TICK;
		if (TestActionTimeAccomulation >= 1000U)
		{
			TestActionTimeAccomulation = 0U;

			// enter test code here on game logic tick:
		}
		//
	}

	inline void RenderTick()
	{
		SystemRender::Render();
		TankTest->onRender();
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
