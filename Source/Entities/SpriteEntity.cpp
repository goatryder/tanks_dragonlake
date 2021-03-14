#include "SpriteEntity.h"

#include "../GameObjects/LevelStruct.h"

// RenderBase

void SpriteEntity::Initialize()
{
	SpriteEntity::CreateSprite();

	EnableRender();
}

void SpriteEntity::Destroy()
{
	LevelStruct* LevelOwner = GetLevel();

	if (LevelOwner != nullptr)
	{
		LevelOwner->RemoveFromLevel(this);
	}
	
	RenderBase::Destroy();

	delete this;
}

void SpriteEntity::onRender()
{
	DrawSprite(SpriteObj, Position);
}

//

SpriteEntity* SpriteEntity::SpawnBasicSprite(const char* ResourceImagePath, VecInt2D Position, bool bInitialize)
{
	SpriteEntity* SpawnedSprite = new SpriteEntity(ResourceImagePath);
	SpawnedSprite->SetPosition(Position);

	if (bInitialize)
	{
		SpawnedSprite->Initialize();
	}

	return SpawnedSprite;
}
