#pragma once

#include "../Entities/TickInterface.h"
#include "../Entities/RenderBase.h"
#include "HealthInterface.h"

class SpriteEntity;

class Phoenix : public RenderBase, public HealthInterface
{
public:

	Phoenix(SpriteEntity* SpriteObj, VecInt2D Position);
	~Phoenix();

protected:

	SpriteEntity* SpriteObj;

public:

	virtual void onDead() override final;

	virtual void onRender() override final;
	virtual void Destroy() override final;
	virtual void Initialize() override final;

	void SpriteInit();

public:
	static Phoenix* SpawnPhoenix(VecInt2D Position, Anchor Anchor = Anchor::TOP_LEFT, const char* ResourcePath = PHOENIX_PNG, bool bInitialize = false);
};