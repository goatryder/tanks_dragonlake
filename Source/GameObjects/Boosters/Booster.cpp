#include "Booster.h"

#include "../../Entities/SpriteEntity.h"
#include "../LevelStruct.h"

Booster::Booster(SpriteEntity* SpriteObj, VecInt2D Position)
	: SpriteObj(SpriteObj)
{
	this->Position = Position;
	SpriteObj->SetPosition(Position);
}

void Booster::onRender()
{
	SpriteObj->onRender();
}

void Booster::Destroy()
{
	SpriteObj->Destroy();

	RenderBase::Destroy();

	delete this;
}

void Booster::Initialize()
{
	SpriteInit();
	EnableRender();
	EnableCollsion();
}

void Booster::onCollide(RenderBase* Other, CollisionFilter Filter)
{
	LevelStruct* LevelOwner = GetLevel();

	if (LevelOwner != nullptr)
	{
		Tank* CollidedTank = dynamic_cast<Tank*>(Other);
		
		if (CollidedTank != nullptr)
		{
			Activate(LevelOwner, CollidedTank);
			Destroy();
		}
	}
}

void Booster::SpriteInit()
{
	SpriteObj->CreateSprite();
	SetSize(SpriteObj->GetSize());
}
