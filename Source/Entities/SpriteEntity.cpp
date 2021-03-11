#include "SpriteEntity.h"

#include "../GameObjects/LevelStruct.h"

// constructor
SpriteEntity::SpriteEntity(const char* ResourceImagePath)
	: ResourceImagePath(ResourceImagePath)
{
}

// destructor
SpriteEntity::~SpriteEntity()
{
	DestroySprite();
}

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

// wrappers
void SpriteEntity::onRender()
{
	if (SpriteObj == nullptr)
	{
		return;
	}

	drawSprite(SpriteObj, Position.X, Position.Y);
}

void SpriteEntity::CreateSprite()
{
	SpriteObj = createSprite(ResourceImagePath);
	InitSizeBySprite(SpriteObj);
}

void SpriteEntity::DestroySprite()
{
	if (SpriteObj != nullptr)
	{
		destroySprite(SpriteObj);
	}
}

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
