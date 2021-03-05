#pragma once

#include "../Entities/TickInterface.h"
#include "../Entities/RenderBase.h"
#include "HealthInterface.h"

class SpriteEntity;
class Tank;

class Bullet : public RenderBase, public TickInterface, public HealthInterface
{
public:

	Bullet(SpriteEntity* SpriteObj, VecInt2D Position, VecInt2D DirectionVec, int Speed, Tank* Owner);
	~Bullet();

	int Speed;

protected:

	SpriteEntity* SpriteObj;
	VecInt2D DirectionVec;

	Tank* Owner;

public:

	Tank* GetOwner() const { return Owner; }

	virtual void onDamage(int Damage) override;
	virtual void onDead() override;

	virtual void onTick(unsigned int DeltaTime) override;

	virtual void onRender() override;
	virtual void onCollide(RenderBase* Other, CollisionFilter Filter) override;

public:

	static int BulletIndex;
	static Bullet* SpawnBulletSlow(Tank* Owner, VecInt2D Position, Direction Direction, bool bSetRenderEnable = true);
};