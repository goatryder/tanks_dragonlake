#include "SpriteEntity.h"


// constructor
SpriteEntity::SpriteEntity(const char* ResourceImagePath)
{
	this->ResourceImagePath = ResourceImagePath;
	SpriteEntity::CreateSprite();  // call implementation of this class explicitly
	
	InitSizeBySprite(SpriteObj);
}

// destructor
SpriteEntity::~SpriteEntity()
{
	SpriteEntity::DestroySprite(); // call implementation of this class explicitly
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
}

void SpriteEntity::DestroySprite()
{
	if (SpriteObj != nullptr)
	{
		destroySprite(SpriteObj);
	}
}
