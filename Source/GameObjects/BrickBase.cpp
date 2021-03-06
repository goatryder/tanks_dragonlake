#include "BrickBase.h"

#include "../Entities/SpriteEntity.h"

#include "../Helpers/DebugPrint.h"


int BrickBase::BrickIndex = 0;

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

void BrickBase::onDamage(int Damage)
{
	HealthInterface::onDamage(Damage);
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
	RenderBase::onDestroy();

	PRINTF(PrintColor::Red, "delete %s", GetName());

	delete this;
}

BrickBase* BrickBase::SpawnBaseBrick(VecInt2D Position, bool bSetRenderEnable)
{
	SpriteEntity* BrickSprite = new SpriteEntity(BRICK_BASE);

	BrickBase* SpawnedBrick = new BrickBase(BrickSprite, Position, BRICK_BASE_HEALTH);

	std::string Name = "brick_" + std::to_string(BrickIndex);
	SpawnedBrick->SetName(Name);

	if (bSetRenderEnable)
	{
		SpawnedBrick->EnableRender();
	}

	BrickIndex++;

	return SpawnedBrick;
}

