#pragma once

#include "../Entities/TickInterface.h"
#include "../Entities/RenderBase.h"
#include "HealthInterface.h"

class SpriteEntity;

class BrickBase : public RenderBase, public HealthInterface
{
public:

	BrickBase(SpriteEntity* SpriteObj, VecInt2D Position, int Health);
	~BrickBase();

protected:

	SpriteEntity* SpriteObj;

public:

	virtual void onDamage(int Damage) override;
	virtual void onDead() override;

	virtual void onRender() override;
	virtual void onCollide(RenderBase* Other, CollisionFilter Filter) override;
	virtual void onDestroy() override;

public:

	static int BrickIndex;
	static BrickBase* SpawnBaseBrick(VecInt2D Position, bool bSetRenderEnable = true);
};