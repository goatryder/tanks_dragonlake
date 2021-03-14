#include "SpriteFlipFlop.h"


void SpriteFlipFlop::Initialize()
{
	SpriteFlipFlop::CreateSprite();

	EnableRender();

	EnableTick();
}

void SpriteFlipFlop::Destroy()
{
	DisableTick();

	SpriteEntity::Destroy();
}

void SpriteFlipFlop::onRender()
{
	if (SpriteObj == nullptr)
		return;

	if (SpriteObjSibling == nullptr)
	{
		DrawSprite(SpriteObj, Position);
		return;
	}

	Sprite* CurrentSpriteObj = bFlipFlop ? SpriteObj : SpriteObjSibling;
	{
		DrawSprite(CurrentSpriteObj, Position);
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
