#include "Framework.h"

#include "Systems/SpritePrototypeManager.h"

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

	// preinitialize resource
	void PreinitializeResources()
	{
		SpritePrototypeManager::CreateSpritePrototype(BG_IMAGE_PATH);

		SpritePrototypeManager::CreateSpritePrototype(TANK_DOWN_0);
		SpritePrototypeManager::CreateSpritePrototype(TANK_DOWN_1);
		SpritePrototypeManager::CreateSpritePrototype(TANK_UP_0);
		SpritePrototypeManager::CreateSpritePrototype(TANK_UP_1);
		SpritePrototypeManager::CreateSpritePrototype(TANK_LEFT_0);
		SpritePrototypeManager::CreateSpritePrototype(TANK_LEFT_1);
		SpritePrototypeManager::CreateSpritePrototype(TANK_RIGHT_0);
		SpritePrototypeManager::CreateSpritePrototype(TANK_RIGHT_1);

		SpritePrototypeManager::CreateSpritePrototype(BRICK_0);
		SpritePrototypeManager::CreateSpritePrototype(BRICK_1);
		SpritePrototypeManager::CreateSpritePrototype(BRICK_BASE);

		SpritePrototypeManager::CreateSpritePrototype(BULLET_UP);
		SpritePrototypeManager::CreateSpritePrototype(BULLET_DOWN);
		SpritePrototypeManager::CreateSpritePrototype(BULLET_RIGHT);
		SpritePrototypeManager::CreateSpritePrototype(BULLET_LEFT);

		SpritePrototypeManager::CreateSpritePrototype(TANK_EB_DOWN_0);
		SpritePrototypeManager::CreateSpritePrototype(TANK_EB_DOWN_1);
		SpritePrototypeManager::CreateSpritePrototype(TANK_EB_UP_0);
		SpritePrototypeManager::CreateSpritePrototype(TANK_EB_UP_1);
		SpritePrototypeManager::CreateSpritePrototype(TANK_EB_LEFT_0);
		SpritePrototypeManager::CreateSpritePrototype(TANK_EB_LEFT_1);
		SpritePrototypeManager::CreateSpritePrototype(TANK_EB_RIGHT_0);
		SpritePrototypeManager::CreateSpritePrototype(TANK_EB_RIGHT_1);

		SpritePrototypeManager::CreateSpritePrototype(PHOENIX_PNG);

		SpritePrototypeManager::CreateSpritePrototype(BOOM_SMALL_0);
		SpritePrototypeManager::CreateSpritePrototype(BOOM_SMALL_1);
		SpritePrototypeManager::CreateSpritePrototype(BOOM_SMALL_2);
		SpritePrototypeManager::CreateSpritePrototype(BOOM_BIG_0);
		SpritePrototypeManager::CreateSpritePrototype(BOOM_BIG_1);

		SpritePrototypeManager::CreateSpritePrototype(FLASHY_0);
		SpritePrototypeManager::CreateSpritePrototype(FLASHY_1);

		SpritePrototypeManager::CreateSpritePrototype(BOOST_HP);

		SpritePrototypeManager::CreateSpritePrototype(WON_UI);
		SpritePrototypeManager::CreateSpritePrototype(LOOSE_UI);
		SpritePrototypeManager::CreateSpritePrototype(TANK_ICO_UI);

		SpritePrototypeManager::CreateSpritePrototype(UI_NUM_0);
		SpritePrototypeManager::CreateSpritePrototype(UI_NUM_1);
		SpritePrototypeManager::CreateSpritePrototype(UI_NUM_2);
		SpritePrototypeManager::CreateSpritePrototype(UI_NUM_3);
		SpritePrototypeManager::CreateSpritePrototype(UI_NUM_4);
		SpritePrototypeManager::CreateSpritePrototype(UI_NUM_5);
		SpritePrototypeManager::CreateSpritePrototype(UI_NUM_6);
		SpritePrototypeManager::CreateSpritePrototype(UI_NUM_7);
		SpritePrototypeManager::CreateSpritePrototype(UI_NUM_8);
		SpritePrototypeManager::CreateSpritePrototype(UI_NUM_9);
	}

	virtual bool Init() 
	{
		// Create all sprite prototypes
		SpritePrototypeManager::Initialize();

		ActiveGameMode.Initialize();

		return true;
	}

	virtual void Close() 
	{
		ActiveGameMode.Finalize();

		// Delete all sprite prototypes
		SpritePrototypeManager::Finalize();
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
	MyFramework* FrameworkInstance = new MyFramework();

	FrameworkInstance->PreinitializeResources();

	return run(FrameworkInstance);
}
