#include "BasicUIElement.h"

#include "../Entities/SpriteEntity.h"


void BasicUIElement::onRender()
{
	if (bEnabled && SpriteObj != nullptr)
	{
		SpriteObj->onRender();
	}
}

void BasicUIElement::Destroy()
{
	if (SpriteObj != nullptr)
		delete SpriteObj;
}

void BasicUIElement::Initialize()
{
	if (SpriteObj != nullptr)
		SpriteObj->CreateSprite();

}

BasicUIElement* BasicUIElement::CreateBasicUIElement(const char* ResourcePath, VecInt2D Position)
{
	SpriteEntity* SpriteObj = SpriteEntity::SpawnBasicSprite(ResourcePath, Position);

	BasicUIElement* SpawnedPopUpUI = new BasicUIElement(SpriteObj);

	return SpawnedPopUpUI;
}
