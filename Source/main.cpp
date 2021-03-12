#include "Framework.h"

#include "GlobalConstants.h"

#include "GameMode.h"

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

	GameMode ActiveGameMode = GameMode();
	PlayerTankController& PlayerController = ActiveGameMode.PlayerController;

	virtual bool Init() 
	{
		ActiveGameMode.Initialize();
		return true;
	}

	virtual void Close() 
	{
		ActiveGameMode.Finalize();
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
		ActiveGameMode.Tick(GAME_LOGIC_TICK);
	}

	inline void RenderTick()
	{
		ActiveGameMode.Render();
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
		PlayerController.onMouseButtonClick(button, isReleased);
	}

	virtual void onKeyPressed(FRKey k) 
	{
		PlayerController.onKeyPressed(k);
	}

	virtual void onKeyReleased(FRKey k) 
	{
		PlayerController.onKeyReleased(k);
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

};

int main(int argc, char *argv[])
{
	return run(new MyFramework);
}
