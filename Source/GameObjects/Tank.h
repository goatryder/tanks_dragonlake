#pragma once

#include "../Entities/TickInterface.h"
#include "../Entities/RenderBase.h"
#include "HealthInterface.h"

class SpriteFlipFlop;

class Bullet;

class Tank : public RenderBase, public TickInterface, public HealthInterface
{
public:

	Tank(SpriteFlipFlop* Left, SpriteFlipFlop* Right, SpriteFlipFlop* Up, SpriteFlipFlop* Down,
		VecInt2D Position, Direction Direction, int Health, int Speed, int MoveAnimSpeed);
	~Tank();

	int Speed;

protected:

	// direction
	SpriteFlipFlop* Left;
	SpriteFlipFlop* Right;
	SpriteFlipFlop* Up;
	SpriteFlipFlop* Down;

	Direction CurrentDirection;
	SpriteFlipFlop* CurrentActiveSprite;

	void ChangeCurrentDirectionSprite(Direction DirectionTo);

	bool bCanMove = false;

	// movement
	void Move(unsigned int DeltaTime);

	// movement anim
	int MoveAnimSpeed;

	void PlayMoveAnim();
	void StopMoveAnim();

	// only one active bullet for player tank allowed
	Bullet* ActiveBullet = nullptr;

public:

	void MoveBegin(Direction DirectionTo);
	void MoveEnd(Direction DirectionTo);

	void Fire();

	Direction GetDirection() const { return CurrentDirection; }

	virtual void onDamage(int Damage) override;
	virtual void onDead() override;

	virtual void onTick(unsigned int DeltaTime) override;

	virtual void onRender() override;
	virtual void onCollide(RenderBase* Other, CollisionFilter Filter) override;

public:

	static int TankIndex;
	static Tank* SpawnTankBasic(VecInt2D Position, Direction Direction, Anchor Anchor = Anchor::TOP_LEFT, bool bSetRenderEnable = true);
	static Tank* SpawnEnemyTankBasic(VecInt2D Position, Direction Direction, Anchor Anchor = Anchor::TOP_LEFT, bool bSetRenderEnable = true);
};