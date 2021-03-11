#include "Bullet.h"

#include "GlobalConstants.h"
#include "../Entities/SpriteEntity.h"
#include "../Helpers/DebugPrint.h"

#include "Tank.h"
#include "HealthInterface.h"
#include "Boom.h"

int Bullet::BulletIndex = 0;

Bullet::Bullet(SpriteEntity* SpriteObj, VecInt2D Position, Direction Dir, int Speed, int Damage, Tank* Owner)
	: SpriteObj(SpriteObj), Dir(Dir), Speed(Speed), Damage(Damage), Owner(Owner)
{
	DirectionVec = DirectionToVec(Dir);
	
	Owner->AddCollidableToIgnore(this);

	this->Position = Position;
}

Bullet::~Bullet()
{
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
		Boom::SpawnBoomSmall(Position);

		HealthInterface* Damagable = dynamic_cast<HealthInterface*>(Other);

		if (Damagable != nullptr)
		{
			Damagable->onDamage(Damage, GetDirectionOposite(Dir));
		}

		Destroy();
	}
}

void Bullet::Initialize()
{
	SpriteInit();
	EnableCollsion();
	EnableRender();
	EnableTick();
}

void Bullet::Destroy()
{
	if (Owner != nullptr)
	{
		Owner->ActiveBullet = nullptr;
	}

	SpriteObj->Destroy();

	DisableTick();
	RenderBase::Destroy();
	
	PRINTF(PrintColor::Red, "delete %s", GetName());

	delete this;
}

void Bullet::SpriteInit()
{
	SpriteObj->CreateSprite();
	SetSize(SpriteObj->GetSize());

	VecInt2D SpawnPositionAdjusted = Position - SpriteObj->GetOppositeSidePosition(Dir);

	this->Position = SpawnPositionAdjusted;
	SpriteObj->SetPosition(SpawnPositionAdjusted);
}

Bullet* Bullet::SpawnBulletSlow(Tank* Owner, VecInt2D Position, Direction Direction, bool bInitialize)
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

	Bullet* SpawnedBullet = new Bullet(SpriteObj, Position, Direction, BULLET_SPEED_SLOW, BULLET_DAMAGE_LOW, Owner);

	std::string Name = Owner->GetName();
	Name += "_bullet_" + std::to_string(BulletIndex);

	SpawnedBullet->SetName(Name);

	if (bInitialize)
	{
		SpawnedBullet->Initialize();
	}

	BulletIndex++;

	return SpawnedBullet;
}
