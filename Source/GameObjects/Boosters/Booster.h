#pragma once

#include "../../Entities/RenderBase.h"

class SpriteEntity;
class Tank;

class Booster : public RenderBase
{
public:

	Booster(SpriteEntity* SpriteObj, VecInt2D Position);
	~Booster() {}

protected:

	SpriteEntity* SpriteObj;

public:

	virtual void Activate(LevelStruct* Level, Tank* BoostedTank) = 0;

	virtual void onRender() override final;
	virtual void Destroy() override final;
	virtual void Initialize() override final;
	virtual void onCollide(RenderBase* Other, CollisionFilter Filter) override final;

	void SpriteInit();

public:

	template <class T>
	static T* SpawnBooster(const char* SpriteResourcePath, VecInt2D Position);
};


