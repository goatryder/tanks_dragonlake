

#include "Framework.h"

#include "GlobalConstants.h"

#include "Structs/VecInt2D.h"
#include "Entities/SpriteEntity.h"
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
		SpriteManager::CreateSprite(BG_IMAGE_PATH);
		SpriteEntity* Tank = SpriteManager::CreateSprite(TANK_BIG_IMAGE_PATH);
		SpriteEntity* Tank2 = SpriteManager::CreateSprite(TANK_IMAGE_PATH);
		
		Tank2->SetPosition(VecInt2D(GAME_AREA_W / 2, GAME_AREA_H / 2));
		//Tank->SetEnable(false);
		//Tank2->SetPosition(VecInt2D(47, 0));
		//
		//PRINTF(PrintColor::Red, "Tank1, Tank2 collision: %d", Tank->CheckCollision(Tank2));
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
