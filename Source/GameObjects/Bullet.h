#pragma once

#include "../Entities/TickInterface.h"
#include "../Entities/RenderInterface.h"
#include "HealthInterface.h"

class SpriteEntity;

class Bullet : public RenderInterface, public TickInterface, public HealthInterface
{
public:

	Bullet(SpriteEntity* SpriteObj, VecInt2D Position, VecInt2D DirectionVec, int Speed);
	~Bullet();

	// params
	int Speed;

protected:

	SpriteEntity* SpriteObj;
	VecInt2D DirectionVec;
	
public:

	virtual void onDamage(int Damage) override;
	virtual void onDead() override;

	virtual void onTick(unsigned int DeltaTime) override;

	virtual void onRender() override;

	// @ToDo: hmmm... Fabric??
	static Bullet* SpawnBulletSlow(Direction Direction, VecInt2D Position);
};