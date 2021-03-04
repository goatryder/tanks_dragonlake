#include "BrickBase.h"

#include "../Entities/SpriteEntity.h"

#include "../Helpers/DebugPrint.h"

#include "../Systems/SystemRender.h"


BrickBase::BrickBase(SpriteEntity* SpriteObj, VecInt2D Position)
	: SpriteObj(SpriteObj)
{
	this->Position = Position;
	
	SpriteObj->SetPosition(Position);
	
	SetSize(SpriteObj->GetSize());
	
	SetHealth(1);
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
	
	SystemRender::RemoveRenderObj(this);
}

void BrickBase::onRender()
{
	SpriteObj->onRender();
}

BrickBase* BrickBase::SpawnBaseBrick(VecInt2D Position, bool bAddToSystemRender)
{
	SpriteEntity* BrickSprite = new SpriteEntity(BRICK_BASE);

	BrickBase* SpawnedBrick = new BrickBase(BrickSprite, Position);

	if (bAddToSystemRender)
	{
		SystemRender::AddRenderObj(SpawnedBrick);
	}

	return SpawnedBrick;
}

