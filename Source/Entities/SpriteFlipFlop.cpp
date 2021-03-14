#include "SpriteFlipFlop.h"
#include "Framework.h"

SpriteFlipFlop::SpriteFlipFlop(const char* ResourceImageRelPathFlip, const char* ResourceImageRelPathFlop, unsigned int FlipFlopTimeMs)
	: SpriteEntity(ResourceImageRelPathFlip),
	ResourceImagePathSibling(GetResourcePath(ResourceImageRelPathFlop)), FlipFlopTime(FlipFlopTimeMs)
{
}

SpriteFlipFlop::~SpriteFlipFlop()
{
}


void SpriteFlipFlop::Initialize()
{
	SpriteEntity::Initialize();

	EnableTick();
}

void SpriteFlipFlop::Destroy()
{
	DisableTick();
	SpriteEntity::Destroy();
}

inline void SpriteFlipFlop::CreateSprite()
{
	SpriteEntity::CreateSprite();

	SpriteObjSibling = createSprite(ResourceImagePathSibling.c_str());
}

inline void SpriteFlipFlop::DestroySprite()
{
	SpriteEntity::DestroySprite();

	if (SpriteObjSibling != nullptr)
	{
		destroySprite(SpriteObjSibling);
	}
}

void SpriteFlipFlop::onRender()
{
	if (SpriteObj == nullptr)
		return;

	if (SpriteObjSibling == nullptr)
	{
		drawSprite(SpriteObj, Position.X, Position.Y);
		return;
	}

	Sprite* CurrentSpriteObj = bFlipFlop ? SpriteObj : SpriteObjSibling;
	{
		drawSprite(CurrentSpriteObj, Position.X, Position.Y);
	}
}

void SpriteFlipFlop::onTick(unsigned int DeltaTime)
{
	TickInterface::onTick(DeltaTime);

	if (FlipFlopTime == 0 || !bAutoFlipFlopEnabled)
		return;
	
	FlipFlopTimeAccomulated += DeltaTime;

	if (FlipFlopTimeAccomulated >= FlipFlopTime)
	{
		bFlipFlop = !bFlipFlop;
		FlipFlopTimeAccomulated = 0;
	}
}
