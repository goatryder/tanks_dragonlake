#include "SpriteEntity.h"

#include "../GameObjects/LevelStruct.h"

SpriteEntity::SpriteEntity(const char* ResourceImagePath)
	: ResourceImagePath(ResourceImagePath)
{
}

SpriteEntity::~SpriteEntity()
{
	DestroySprite();
}

// RenderBase

void SpriteEntity::Initialize()
{
	CreateSprite();
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
	DrawSprite(Position);
}

//

// wrappers

inline void SpriteEntity::CreateSprite()
{
	SpriteObj = createSprite(ResourceImagePath);
	InitSizeBySprite(SpriteObj);
}

inline void SpriteEntity::DestroySprite()
{
	if (SpriteObj != nullptr)
	{
		destroySprite(SpriteObj);
		SpriteObj = nullptr;
	}
}

inline void SpriteEntity::DrawSprite(VecInt2D DrawPosition)
{
	if (SpriteObj == nullptr)
	{
		return;
	}

	drawSprite(SpriteObj, DrawPosition.X, DrawPosition.Y);
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
