#include "SpriteFlipFlop.h"
#include "Framework.h"

SpriteFlipFlop::SpriteFlipFlop(const char* ResourceImagePathFlip)
	: SpriteEntity(ResourceImagePathFlip)
{
}

SpriteFlipFlop::SpriteFlipFlop(const char* ResourceImagePathFlip, const char* ResourceImagePathFlop)
	: SpriteEntity(ResourceImagePathFlip)
{
	ResourceImagePathSibling = ResourceImagePathFlop;

	SpriteFlipFlop::CreateSprite();  // call implementation of this class explicitly
}

SpriteFlipFlop::~SpriteFlipFlop()
{
	SpriteFlipFlop::DestroySprite();  // call implementation of this class explicitly
}

void SpriteFlipFlop::FlopSpriteInitLazy(const char* ResourceImagePathFlop)
{
	if (SpriteObjSibling != nullptr) // already initialized
		return;

	ResourceImagePathSibling = ResourceImagePathFlop;

	SpriteFlipFlop::CreateSprite();  // call implementation of this class explicitly
}

void SpriteFlipFlop::DrawSprite()
{
	if (!bEnabled)
		return;
	
	if (SpriteObj == nullptr)
		return;

	if (SpriteObjSibling == nullptr) // probably initialized as SprityEntity, act accordingly
	{
		drawSprite(SpriteObj, Position.X, Position.Y);
		return;
	}

	Sprite* CurrentSpriteObj = bFlipFlop ? SpriteObj : SpriteObjSibling;
	{
		drawSprite(CurrentSpriteObj, Position.X, Position.Y);
		bFlipFlop = !bFlipFlop;
	}
}

inline void SpriteFlipFlop::CreateSprite()
{
	SpriteObjSibling = createSprite(ResourceImagePathSibling);
}

inline void SpriteFlipFlop::DestroySprite()
{
	if (SpriteObjSibling != nullptr)
	{
		destroySprite(SpriteObjSibling);
	}
}
