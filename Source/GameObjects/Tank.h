#pragma once

#include "../Entities/TickInterface.h"
#include "../Entities/RenderInterface.h"
#include "HealthInterface.h"

class SpriteFlipFlop;


class Tank : public RenderInterface, public TickInterface, public HealthInterface
{
public:

	Tank(SpriteFlipFlop* Left, SpriteFlipFlop* Right, SpriteFlipFlop* Up, SpriteFlipFlop* Down);
	~Tank();
	
	// params
	int Speed;
	// *bullet class ref*;

protected:

	// direction
	SpriteFlipFlop* Left;
	SpriteFlipFlop* Right;
	SpriteFlipFlop* Up;
	SpriteFlipFlop* Down;

	Direction CurrentDirection;
	SpriteFlipFlop* CurrentActiveSprite;

	void ChangeCurrentDirectionSprite(Direction DirectionTo)
	{
		if (DirectionTo == CurrentDirection) return;

		if (DirectionTo == Direction::UP) CurrentActiveSprite = Up;
		else if (DirectionTo == Direction::DOWN) CurrentActiveSprite = Down;
		else if (DirectionTo == Direction::LEFT) CurrentActiveSprite = Left;
		else CurrentActiveSprite = Right;

		CurrentDirection = DirectionTo;
	}

	bool bCanMove = false;

	// movement
	void Move();

	// movement anim

	int MoveAnimSpeed;

	void PlayMoveAnim();
	void StopMoveAnim();

public:

	void MoveBegin(Direction DirectionTo);
	void MoveEnd(Direction DirectionTo);
	
	void Fire();

	Direction GetDirection() const { return CurrentDirection; }

	virtual void onDamage(int Damage) override;
	virtual void onDead() override;

	virtual void onTick(unsigned int DeltaTime) override;

	virtual void onRender() override;
};