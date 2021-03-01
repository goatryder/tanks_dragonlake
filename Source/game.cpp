

#include "Framework.h"

#include "GlobalConstants.h"

#include "Structs/VecInt2D.h"
#include "Entities/SpriteEntity.h"
#include "Entities/SpriteFlipFlop.h"
#include "Managers/SpriteManager.h"

#include "Helpers/DebugPrint.h"

/* Test Framework realization */
class MyFramework : public Framework {

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = 208; 
		height = 208;
		fullscreen = false;
	}

	virtual bool Init() 
	{
		SpriteManager::CreateSprite<SpriteEntity>(BG_IMAGE_PATH);

		SpriteFlipFlop* Tank = SpriteManager::CreateSprite<SpriteFlipFlop>(TANK0_G_UP_1);
		Tank->FlopSpriteInitLazy(TANK0_UP_0);

		return true;
	}

	virtual void Close() 
	{

	}

	virtual bool Tick() 
	{
		SpriteManager::DrawSprites();
		return false;
	}

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
	
	virtual const char* GetTitle() override
	{
		return "Tanki";
	}
};

int main(int argc, char *argv[])
{
	return run(new MyFramework);
}
