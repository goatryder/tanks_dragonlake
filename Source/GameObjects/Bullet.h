#pragma once

#include "../Entities/TickInterface.h"
#include "../Entities/RenderBase.h"

class SpriteEntity;
class Tank;

class Bullet : public RenderBase, public TickInterface
{
public:

	Bullet(SpriteEntity* SpriteObj, VecInt2D Position, Direction Dir, int Speed, int Damage, Tank* Owner);
	~Bullet();

	int Speed;
	int Damage;

protected:

	SpriteEntity* SpriteObj;
	VecInt2D DirectionVec;
	Direction Dir;


public:

	Tank* Owner;

	virtual void onTick(unsigned int DeltaTime) override final;

	virtual void onRender() override final;
	virtual void onCollide(RenderBase* Other, CollisionFilter Filter) override final;
	virtual void Initialize() override final;
	virtual void Destroy() override final;

	void SpriteInit();

public:

	static int BulletIndex;
	static Bullet* SpawnBulletSlow(Tank* Owner, VecInt2D Position, Direction Direction, bool bInitialize = true);
};