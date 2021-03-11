#include "BrickBase.h"

#include "../Entities/SpriteEntity.h"

#include "BrickBlock.h"

#include "../Helpers/DebugPrint.h"


int BrickBase::BrickCount = 0;

BrickBase::BrickBase(SpriteEntity* SpriteObj, VecInt2D Position, int Health)
	: SpriteObj(SpriteObj)
{
	this->Position = Position;
	SetHealth(Health, true);
}

BrickBase::~BrickBase()
{
}

void BrickBase::Destroy()
{
	if (Owner != nullptr)
	{
		Owner->OwnedBrickDestroyed(OwnerIndex);
	}

	SpriteObj->Destroy();

	RenderBase::Destroy();

	PRINTF(PrintColor::Red, "delete %s", GetName());

	delete this;
}

void BrickBase::Initialize()
{
	SpriteInit();
	EnableCollsion();
	EnableRender();
}

void BrickBase::SpriteInit()
{
	SpriteObj->CreateSprite();
	SetSize(SpriteObj->GetSize());
	SpriteObj->SetPosition(Position);
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
	Destroy();
}

void BrickBase::onRender()
{
	// PRINTF(PrintColor::Yellow, "BrickBase onRender(): name=%s, pos X=%d, Y=%d", GetName(), SpriteObj->GetPosition().X, SpriteObj->GetPosition().Y);
	SpriteObj->onRender();
}

BrickBase* BrickBase::SpawnBaseBrick(VecInt2D Position, const char* ResourcePath, int Health, bool bInitialize)
{
	SpriteEntity* BrickSprite = new SpriteEntity(ResourcePath);

	BrickBase* SpawnedBrick = new BrickBase(BrickSprite, Position, Health);

	std::string Name = "brick_" + std::to_string(BrickCount);
	SpawnedBrick->SetName(Name);

	if (bInitialize)
	{
		SpawnedBrick->Initialize();
	}

	BrickCount++;

	return SpawnedBrick;
}

