#include "BrickBase.h"

#include "../Entities/SpriteEntity.h"

#include "../Helpers/DebugPrint.h"


int BrickBase::BrickIndex = 0;

BrickBase::BrickBase(SpriteEntity* SpriteObj, VecInt2D Position)
	: SpriteObj(SpriteObj)
{
	this->Position = Position;
	
	SpriteObj->SetPosition(Position);
	
	SetSize(SpriteObj->GetSize());
	
	SetHealth(1);

	EnableCollsion();
}

BrickBase::~BrickBase()
{
	delete SpriteObj;
	SpriteObj = nullptr;
}

void BrickBase::onDamage(int Damage)
{
	PRINTF(PrintColor::Green, "BRICK %d damage recieved", Damage);
}

void BrickBase::onDead()
{
	PRINT(PrintColor::Green, "BRICK died");
}

void BrickBase::onRender()
{
	SpriteObj->onRender();
}

void BrickBase::onCollide(RenderBase* Other)
{
	PRINT(PrintColor::Green, "BRICK collided");
}

BrickBase* BrickBase::SpawnBaseBrick(VecInt2D Position, bool bSetRenderEnable)
{
	SpriteEntity* BrickSprite = new SpriteEntity(BRICK_BASE);

	BrickBase* SpawnedBrick = new BrickBase(BrickSprite, Position);

	std::string Name = "brick_" + std::to_string(BrickIndex);
	SpawnedBrick->SetName(Name);

	if (bSetRenderEnable)
	{
		SpawnedBrick->EnableRender();
	}

	BrickIndex++;

	return SpawnedBrick;
}

