#include "SpriteEntity.h"
#include "../Framework.h"


// constructor
SpriteEntity::SpriteEntity(const char* path)
{
	ResourceImagePath = path;
	
	CreateSprite();
	InitSpriteSize();
	
	bEnabled = true;
}

// destructor
SpriteEntity::~SpriteEntity()
{
	DestroySprite();
}

// draw controllers
bool SpriteEntity::GetEnable()
{
	return bEnabled;
}

void SpriteEntity::SetEnable(bool Val)
{
	bEnabled = Val;
}

const VecInt2D SpriteEntity::GetSize()
{
	return Size;
}

const VecInt2D SpriteEntity::GetPosition()
{
	return Position;
}

void SpriteEntity::SetPosition(VecInt2D Val)
{
	Position = Val;
}

// check collision
bool SpriteEntity::CheckCollision(SpriteEntity* OtherEntity)
{
	if (OtherEntity == nullptr)
	{
		return false;
	}

	VecInt2D DeltaPos = (Position - OtherEntity->GetPosition()).GetAbs();
	VecInt2D MaxSize = VecInt2D::GetMax(Size, OtherEntity->GetSize());

	if (DeltaPos.X >= MaxSize.X || DeltaPos.Y >= MaxSize.Y)
	{
		return false;
	}

	return true;
}

// wrappers
void SpriteEntity::DrawSprite()
{
	if (SpriteObj == nullptr)
	{
		return;
	}

	if (bEnabled)
	{
		drawSprite(SpriteObj, Position.X, Position.Y);
	}
}

void SpriteEntity::CreateSprite()
{
	SpriteObj = createSprite(ResourceImagePath);
}

void SpriteEntity::DestroySprite()
{
	destroySprite(SpriteObj);
}

void SpriteEntity::InitSpriteSize()
{
	int w, h;
	getSpriteSize(SpriteObj, w, h);
	Size = VecInt2D(w, h);
}
//