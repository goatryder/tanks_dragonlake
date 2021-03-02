

#include "Framework.h"

#include "GlobalConstants.h"
#include "Helpers/DebugPrint.h"
#include "Structs/VecInt2D.h"

#include "Entities/SpriteEntity.h"
#include "Entities/SpriteFlipFlop.h"

#include "Managers/SpriteManager.h"
#include "Systems/SystemTick.h"


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
		width = 208; 
		height = 208;
		fullscreen = false;
	}

	SpriteFlipFlop* Tank = nullptr;

	virtual bool Init() 
	{
		SpriteManager::CreateSprite<SpriteEntity>(BG_IMAGE_PATH);

		Tank = SpriteManager::CreateSprite<SpriteFlipFlop>(TANK0_G_UP_1);
		Tank->FlopSpriteInitLazy(TANK0_UP_0, 250U);

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
		SpriteManager::DrawSprites();
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
	}

	virtual void onKeyReleased(FRKey k) 
	{
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

};

int main(int argc, char *argv[])
{
	return run(new MyFramework);
}
