#include "BrickBase.h"

#include "../Entities/SpriteEntity.h"

#include "BrickBlock.h"

#include "../Helpers/DebugPrint.h"


int BrickBase::BrickCount = 0;

BrickBase::BrickBase(SpriteEntity* SpriteObj, VecInt2D Position, int Health)
	: SpriteObj(SpriteObj)
{
	this->Position = Position;
	
	SpriteObj->SetPosition(Position);
	
	SetSize(SpriteObj->GetSize());
	
	SetHealth(Health);

	EnableCollsion();
}

BrickBase::~BrickBase()
{
	delete SpriteObj;
}

void BrickBase::onDamage(int Damage, Direction From)
{
	if (Owner != nullptr)
	{
		Owner->OwnedBrickDamaged(OwnerIndex, Damage, From);
	}
	else
	{
		HealthInterface::onDamage(Damage, From);
	}
}

void BrickBase::onDead()
{
	onDestroy();
}

void BrickBase::onRender()
{
	SpriteObj->onRender();
}

void BrickBase::onCollide(RenderBase* Other, CollisionFilter Filter)
{
}

void BrickBase::onDestroy()
{
	if (Owner != nullptr)
	{
		Owner->OwnedBrickDestroyed(OwnerIndex);
	}

	RenderBase::onDestroy();

	PRINTF(PrintColor::Red, "delete %s", GetName());

	delete this;
}

BrickBase* BrickBase::SpawnBaseBrick(VecInt2D Position, const char* ResourcePath, int Health, bool bSetRenderEnable)
{
	SpriteEntity* BrickSprite = new SpriteEntity(ResourcePath);

	BrickBase* SpawnedBrick = new BrickBase(BrickSprite, Position, Health);

	std::string Name = "brick_" + std::to_string(BrickCount);
	SpawnedBrick->SetName(Name);

	if (bSetRenderEnable)
	{
		SpawnedBrick->EnableRender();
	}

	BrickCount++;

	return SpawnedBrick;
}

