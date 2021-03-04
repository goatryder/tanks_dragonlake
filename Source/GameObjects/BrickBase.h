#pragma once

#include "../Entities/TickInterface.h"
#include "../Entities/RenderInterface.h"
#include "HealthInterface.h"

class SpriteEntity;

class BrickBase : public RenderInterface, public HealthInterface
{
public:

	BrickBase(SpriteEntity* SpriteObj, VecInt2D Position);
	~BrickBase();

protected:

	SpriteEntity* SpriteObj;

public:

	virtual void onDamage(int Damage) override;
	virtual void onDead() override;

	virtual void onRender() override;

	// @ToDo: hmmm... Fabric??
	static BrickBase* SpawnBaseBrick(VecInt2D Position, bool bAddToSystemRender = true);
};