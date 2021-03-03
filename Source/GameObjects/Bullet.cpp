#include "Bullet.h"

#include "../Entities/SpriteEntity.h"
#include "GlobalConstants.h"


Bullet::Bullet(SpriteEntity* SpriteObj, VecInt2D Position, VecInt2D DirectionVec, int Speed)
	: SpriteObj(SpriteObj), DirectionVec(DirectionVec), Speed(Speed)
{
	this->Position = Position;
	
	Size = SpriteObj->GetSize();
}

Bullet::~Bullet()
{
	delete SpriteObj;
}

void Bullet::onDamage(int Damage)
{
}

void Bullet::onDead()
{
}

void Bullet::onTick(unsigned int DeltaTime)
{
	VecInt2D NewPosition = DirectionVec * (((Speed * DeltaTime) >> 10) + 1) + Position;
	SetPosition(NewPosition, true);
}

void Bullet::onRender()
{
	SpriteObj->SetPosition(Position);
	SpriteObj->onRender();
}

Bullet* Bullet::SpawnBulletSlow(Direction Direction, VecInt2D Position)
{
	const char* ResourcePath;

	switch (Direction)
	{
	case Direction::RIGHT:
		ResourcePath = BULLET_RIGHT;
		break;
	case Direction::DOWN:
		ResourcePath = BULLET_DOWN;
		break;
	case Direction::LEFT:
		ResourcePath = BULLET_LEFT;
		break;
	default:
		ResourcePath = BULLET_UP;
		break;
	}

	SpriteEntity* SpriteObj = new SpriteEntity(ResourcePath);

	Bullet* SpawnedBullet = new Bullet(
		SpriteObj, Position - SpriteObj->GetCenterPosition(), DirectionToVec(Direction), BULLET_SPEED_SLOW);

	return SpawnedBullet;
}
