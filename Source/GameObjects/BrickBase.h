#pragma once

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

	virtual void onDamage(int Damage, Direction From) override final;
	virtual void onDead() override final;

	virtual void onRender() override final;
	virtual void Destroy() override final;
	virtual void Initialize() override final;

	void SpriteInit();

public:

	static int BrickCount;
	static BrickBase* SpawnBaseBrick(VecInt2D Position, const char* ResourcePath = BRICK_BASE, int Health = BRICK_BASE_HEALTH, bool bInitialize = false);
};