#include "Bullet.h"

#include "GlobalConstants.h"
#include "../Entities/SpriteEntity.h"
#include "../Helpers/DebugPrint.h"

#include "Tank.h"
#include "HealthInterface.h"

int Bullet::BulletIndex = 0;

Bullet::Bullet(SpriteEntity* SpriteObj, VecInt2D Position, VecInt2D DirectionVec, int Speed, int Damage, Tank* Owner)
	: SpriteObj(SpriteObj), DirectionVec(DirectionVec), Speed(Speed), Damage(Damage), Owner(Owner)
{
	Owner->AddCollidableToIgnore(this);

	this->Position = Position;
	SpriteObj->SetPosition(Position);
	
	Size = SpriteObj->GetSize();

	EnableCollsion();
	EnableTick();
}

Bullet::~Bullet()
{
	delete SpriteObj;
}

void Bullet::onTick(unsigned int DeltaTime)
{
	VecInt2D NewPosition = DirectionVec * (((Speed * DeltaTime) >> 10) + 1) + Position;
	SetPosition(NewPosition, true);
	SpriteObj->SetPosition(Position);
}

void Bullet::onRender()
{
	SpriteObj->onRender();
}

void Bullet::onCollide(RenderBase* Other, CollisionFilter Filter)
{
	if (Filter == CollisionFilter::CF_BLOCK)
	{
		HealthInterface* Damagable = dynamic_cast<HealthInterface*>(Other);

		if (Damagable != nullptr)
		{
			Damagable->onDamage(Damage);
		}

		onDestroy();
	}
}

void Bullet::onDestroy()
{
	if (Owner != nullptr)
	{
		Owner->ActiveBullet = nullptr;
	}

	DisableTick();
	RenderBase::onDestroy();
	
	PRINTF(PrintColor::Red, "delete %s", GetName());

	delete this;
}

Bullet* Bullet::SpawnBulletSlow(Tank* Owner, VecInt2D Position, Direction Direction, bool bSetRenderEnable)
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
	
	VecInt2D SpawnLocation = Position - SpriteObj->GetOppositeSidePosition(Direction);

	Bullet* SpawnedBullet = new Bullet(SpriteObj, SpawnLocation, DirectionToVec(Direction), BULLET_SPEED_SLOW, BULLET_DAMAGE_LOW, Owner);

	std::string Name = Owner->GetName();
	Name += "_bullet_" + std::to_string(BulletIndex);

	SpawnedBullet->SetName(Name);

	if (bSetRenderEnable)
	{
		SpawnedBullet->EnableRender();
	}

	BulletIndex++;

	return SpawnedBullet;
}
