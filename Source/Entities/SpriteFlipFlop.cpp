#include "SpriteFlipFlop.h"
#include "Framework.h"

SpriteFlipFlop::SpriteFlipFlop(const char* ResourceImagePathFlip)
	: SpriteEntity(ResourceImagePathFlip)
{
}

SpriteFlipFlop::SpriteFlipFlop(const char* ResourceImagePathFlip, const char* ResourceImagePathFlop, unsigned int FlipFlopTimeMs)
	: SpriteEntity(ResourceImagePathFlip)
{
	ResourceImagePathSibling = ResourceImagePathFlop;

	SpriteFlipFlop::CreateSprite();  // call implementation of this class explicitly

	FlipFlopTime = FlipFlopTimeMs;
}

SpriteFlipFlop::~SpriteFlipFlop()
{
	SpriteFlipFlop::DestroySprite();  // call implementation of this class explicitly
}

void SpriteFlipFlop::FlopSpriteInitLazy(const char* ResourceImagePathFlop, unsigned int FlipFlopTimeMs)
{
	if (SpriteObjSibling != nullptr) // already initialized
		return;

	ResourceImagePathSibling = ResourceImagePathFlop;

	SpriteFlipFlop::CreateSprite();  // call implementation of this class explicitly

	FlipFlopTime = FlipFlopTimeMs;
}

void SpriteFlipFlop::onRender()
{
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
	}
}

void SpriteFlipFlop::onDestroy()
{
	DisableTick();
	SpriteEntity::onDestroy();

	delete this;
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
