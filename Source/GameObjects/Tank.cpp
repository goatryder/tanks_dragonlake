#include "Tank.h"

#include "../Entities/SpriteFlipFlop.h"

#include "../Helpers/DebugPrint.h"
#include "../GlobalConstants.h"

// @ToDo Tank Fabric, hehe)
Tank::Tank(SpriteFlipFlop* Left, SpriteFlipFlop* Right, SpriteFlipFlop* Up, SpriteFlipFlop* Down)
	: Left(Left), Right(Right), Up(Up), Down(Down)
{
	// defaults
	Health = TANK_HEALTH_BASIC;
	Speed = TANK_SPEED_SLOW;

	SetSize(Left->GetSize());
	//SetPosition(Left->GetPosition());

	CurrentDirection = Direction::UP;
	CurrentActiveSprite = Up;

	// Set anim speed
	MoveAnimSpeed = TANK_SPEED_SLOW_ANIM_TIME;

	Left->SetFlipFlopTime(MoveAnimSpeed);
	Left->SetAutoFlipFlopEnable(false);
	Right->SetFlipFlopTime(MoveAnimSpeed);
	Right->SetAutoFlipFlopEnable(false);
	Up->SetFlipFlopTime(MoveAnimSpeed);
	Up->SetAutoFlipFlopEnable(false);
	Down->SetFlipFlopTime(MoveAnimSpeed);
	Down->SetAutoFlipFlopEnable(false);
}

Tank::~Tank()
{
	delete Left;
	delete Right;
	delete Up;
	delete Down;
}

void Tank::PlayMoveAnim()
{
	CurrentActiveSprite->SetAutoFlipFlopEnable(true);
}

void Tank::StopMoveAnim()
{
	CurrentActiveSprite->SetAutoFlipFlopEnable(false);
}

void Tank::MoveBegin(Direction DirectionTo)
{
	// PRINTF(PrintColor::Green, "Tank Start Moving To %s", DirectionToString(DirectionTo));

	bCanMove = true;

	ChangeCurrentDirectionSprite(DirectionTo);

	PlayMoveAnim();
}

void Tank::MoveEnd(Direction DirectionTo)
{
	if (DirectionTo != CurrentDirection)  // do not execute when two key are pressed then one of them is released
		return;

	bCanMove = false;

	StopMoveAnim();

	//PRINT(PrintColor::Green, "Tank Stop Movement, Auto FlipFlop is Active:");
	//PRINTF(PrintColor::Green, "Left %d",	Left->IsAutoFlipFlopEnabled());
	//PRINTF(PrintColor::Green, "Right %d",	Right->IsAutoFlipFlopEnabled());
	//PRINTF(PrintColor::Green, "Up %d",		Up->IsAutoFlipFlopEnabled());
	//PRINTF(PrintColor::Green, "Down %d",	Down->IsAutoFlipFlopEnabled());
}

void Tank::Move()
{
	if (!bCanMove)
		return;

	// PRINT(PrintColor::Green, "Tank Move");
}

void Tank::Fire()
{
	PRINT(PrintColor::Green, "Tank shooted");

	// @ToDo base bullet class, spawn it

}

void Tank::onDamage(int Damage)
{
	HealthInterface::onDamage(Damage);

	PRINTF(PrintColor::Green, "Tank %d damage recieved", Damage);
}

void Tank::onDead()
{
	HealthInterface::onDead();

	PRINT(PrintColor::Green, "Tank died");
}

void Tank::onTick(unsigned int DeltaTime)
{
	TickInterface::onTick(DeltaTime);

	if (!bIsDead)
	{
		Move();
	}
}

void Tank::onRender()
{
	CurrentActiveSprite->SetPosition(Position);
	CurrentActiveSprite->onRender();
}
