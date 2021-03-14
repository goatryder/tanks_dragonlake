#include "SpriteSequence.h"

void SpriteSequence::Initialize()
{
	SpriteEntity::Initialize();

	SpriteSequence::CreateSprite();

	EnableTick();
}

void SpriteSequence::Destroy()
{
	DisableTick();

	SpriteEntity::Destroy();
}

void SpriteSequence::onTick(unsigned int DeltaTime)
{
	AnimTimeAccomulated += DeltaTime;

	if (AnimTimeAccomulated >= AnimTime)
	{
		AnimTimeAccomulated = 0;

		if (bDestroyOnFirstLoopFinish && bFirstLoopFinish)
		{
			Destroy();
			return;
		}
		
		int NewSpriteIndex = (CurrentSpriteObjIndex + 1) % SpriteObjVecSize;

		if (NewSpriteIndex + 1 == SpriteObjVecSize)
		{
			bFirstLoopFinish = true;
		}

		CurrentSpriteObjIndex = NewSpriteIndex;

		SpriteObj = SpriteObjVec[NewSpriteIndex];
	}
}

SpriteSequence* SpriteSequence::SpawnSpriteSequence(std::vector<const char*> ResourceImageRelPathVec, VecInt2D Position, unsigned int AnimTime, bool bInitialize)
{
	SpriteSequence* SpawnedSprite = new SpriteSequence(ResourceImageRelPathVec, AnimTime);
	SpawnedSprite->SetPosition(Position);

	if (bInitialize)
	{
		SpawnedSprite->Initialize();
	}

	return SpawnedSprite;
}
