#pragma once

#include "../Entities/TickInterface.h"
#include "../Entities/RenderBase.h"
#include "HealthInterface.h"

class SpriteEntity;
class BrickBlock;

class BrickBase : public RenderBase, public HealthInterface
{
public:

	BrickBase(SpriteEntity* SpriteObj, VecInt2D Position, int Health);
	~BrickBase();

protected:

	SpriteEntity* SpriteObj;

public:

	BrickBlock* Owner = nullptr;
	int OwnerIndex = -1;

	virtual void onDamage(int Damage, Direction From) override;
	virtual void onDead() override;

	virtual void onRender() override;
	virtual void onCollide(RenderBase* Other, CollisionFilter Filter) override;
	virtual void onDestroy() override;

public:

	static int BrickIndex;
	static BrickBase* SpawnBaseBrick(VecInt2D Position, bool bSetRenderEnable = true);
};