#include "Tank.h"

#include "../Entities/SpriteFlipFlop.h"

#include "../Helpers/DebugPrint.h"

#include "Bullet.h"

#include "Boom.h"

#include "GameMode.h"

#include "../GameObjects/Boosters/BoosterHP.h"

TankSpawnPoint TankSpawnPoint::BottomLeftSpawnPoint(VecInt2D(GAME_AREA_W0, GAME_AREA_H1), Direction::UP, Anchor::BOTTOM_LEFT);
TankSpawnPoint TankSpawnPoint::BottomRightSpawnPoint(VecInt2D(GAME_AREA_W1, GAME_AREA_H1), Direction::UP, Anchor::BOTTOM_RIGHT);
TankSpawnPoint TankSpawnPoint::TopLeftSpawnPoint(VecInt2D(GAME_AREA_W0, GAME_AREA_H0), Direction::DOWN, Anchor::TOP_LEFT);
TankSpawnPoint TankSpawnPoint::TopRightSpawnPoint(VecInt2D(GAME_AREA_W1, GAME_AREA_H0), Direction::DOWN, Anchor::TOP_RIGHT);
TankSpawnPoint TankSpawnPoint::TopCenterSpawnPoint(VecInt2D(GAME_AREA_W1 / 2, GAME_AREA_H0), Direction::DOWN, Anchor::TOP);

int Tank::TankCount = 0;

Tank::Tank(SpriteFlipFlop* Left, SpriteFlipFlop* Right, SpriteFlipFlop* Up, SpriteFlipFlop* Down,
	VecInt2D Position, Direction Direction, int Health, int Speed, int MoveAnimSpeed)
	: Left(Left), Right(Right), Up(Up), Down(Down), Speed(Speed), MoveAnimSpeed(MoveAnimSpeed)
{
	SetHealth(Health, true);
	SetPosition(Position);

	SetNextDirectionSprite(Direction);
	ChangeCurrentDirectionSprite();

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
}

void Tank::SetNextDirectionSprite(Direction DirectionTo)
{
	if (DirectionTo == NextDirection) return;

	NextDirection = DirectionTo;

	switch (NextDirection)
	{
	case Direction::RIGHT:
		NextActiveSprite = Right;
		break;
	case Direction::DOWN:
		NextActiveSprite = Down;
		break;
	case Direction::LEFT:
		NextActiveSprite = Left;
		break;
	default:
		NextActiveSprite = Up;
		break;
	}
}

void Tank::ChangeCurrentDirectionSprite()
{
	CurrentDirection = NextDirection;
	CurrentActiveSprite = NextActiveSprite;
	CurrentActiveSprite->SetPosition(Position);
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
	SetNextDirectionSprite(DirectionTo);

	PlayMoveAnim();

	bCanMove = true;
}

void Tank::MoveEnd(Direction DirectionTo)
{
	if (DirectionTo != NextDirection)  // do not execute when two key are pressed then one of them is released
		return;

	bCanMove = false;

	StopMoveAnim();
}

void Tank::Move(unsigned int DeltaTime)
{
	if (!bCanMove) return;

	if (NextDirection != CurrentDirection && bPrevPositionRelevent)
	{
		SetPosition(PrevPosition);
	}
	else
	{
		VecInt2D PositionDelta = DirectionToVec(CurrentDirection) * (((Speed * DeltaTime) >> 10) + 1);
		VecInt2D NewPosition = GetPosition() + PositionDelta;
		SetPosition(NewPosition, true);
	}

	ChangeCurrentDirectionSprite();
}

void Tank::Fire()
{
	if (bPossessedByPlayer && ActiveBullet != nullptr) // only one active bullet allowed for player
	{
		return;
	}

	// PRINTF(PrintColor::Blue, "%s shooted", GetName());

	VecInt2D BulletSpawnPosition = GetSidePosition(CurrentDirection);

	ActiveBullet = Bullet::SpawnBulletSlow(this, BulletSpawnPosition, CurrentDirection);
}

void Tank::onDamage(int Damage, Direction From)
{
	// PRINTF(PrintColor::Green, "%s recieved %d damage", GetName(), Damage);
	
	if (FlashyEffectTimer > 0)  // spawn kill protection
	{
		return;
	}
	
	HealthInterface::onDamage(Damage, From);
}

void Tank::onDead()
{
	PRINTF(PrintColor::Green, "%s died", GetName());

	LevelStruct* LevelOwner = GetLevel();
	
	if (LevelOwner != nullptr) 
	{
		if (LevelOwner->PlayerTank == this)  // check if player tank
		{
			LevelOwner->PlayerRespawnNum--;

			if (LevelOwner->PlayerRespawnNum >= 0)
			{
				Respawn(LevelOwner->PlayerSpawnPoint);  // respawn player tank

				PRINTF(PrintColor::Green, "%s respawned", GetName());

				return;
			}
			
		}
		else // enemy died
		{
			LevelOwner->EnemyTankKillLeft--;
		}

		if (bDropPickableOnDeath)
		{
			// @ToDo: random boost spawner
			BoosterHP::SpawnPlayerHPBooster(LevelOwner, Position);
			PRINTF(PrintColor::Yellow, "%s dropped boost", GetName());
		}
	}
	
	Boom::SpawnBoomBig(Position);

	Destroy();
}

void Tank::onTick(unsigned int DeltaTime)
{
	TickInterface::onTick(DeltaTime);

	if (!IsDead())
	{
		Move(DeltaTime);
	}

	// FlashyEffect
	if (bFlashyEffectEnabled && FlashyEffect != nullptr)
	{
		FlashyEffect->SetPosition(Position);

		if (FlashyEffectTimer > 0)
		{
			FlashyEffectTimer -= DeltaTime;

			if (FlashyEffectTimer <= 0)
			{
				DisableFlashyEffect();
			}
		}
	}
}

void Tank::onRender()
{
	CurrentActiveSprite->onRender();
	
	if (!bFlashyEffectEnabled)
		return;

	if (FlashyEffect != nullptr)
	{
		FlashyEffect->onRender();
	}
}

void Tank::onCollide(RenderBase* Other, CollisionFilter Filter)
{
	// PRINTF(PrintColor::Green, "TANK %s Collided With: %s", GetName(), Other->GetName());
}

void Tank::Initialize()
{
	InitSprite();

	LevelStruct* LevelOwner = GetLevel();

	if (LevelOwner != nullptr)
	{
		if (LevelOwner->PlayerTank == this) 
		{
			bPossessedByPlayer = true;
		}
		else  // if tank not player tank, it's should be enemy tank, add to ai controlller
		{
			GameMode* LevelGameMode = LevelOwner->GameModeOwner;

			if (LevelGameMode != nullptr)
			{
				LevelGameMode->AIController.AddTank(this);
			}
		}
	}

	if (bDropPickableOnDeath)
	{
		EnableFlashyEffect(0); // enable permanent flashy effect
	}

	EnableCollsion();
	EnableTick();
	EnableRender();
}

void Tank::Destroy()
{
	RenderBase::Destroy();

	LevelStruct* LevelOwner = GetLevel();
	if (LevelOwner != nullptr)
	{
		GameMode* LevelGameMode = LevelOwner->GameModeOwner;

		if (LevelGameMode != nullptr)
		{ 
			if (LevelOwner->PlayerTank == this)  // remove player tank from controller
			{
				LevelGameMode->PlayerController.PlayerTank = nullptr;
			}
			else // remove ai tank from controller
			{
				LevelGameMode->AIController.RemoveTank(this);
			}
		}
	}

	if (ActiveBullet != nullptr)
	{
		ActiveBullet->Owner = nullptr;
	}

	if (FlashyEffect != nullptr)
	{
		FlashyEffect->Destroy();
	}

	if (Left != nullptr) Left->Destroy();
	if (Right != nullptr) Right->Destroy();
	if (Up != nullptr) Up->Destroy();
	if (Down != nullptr) Down->Destroy();

	DisableTick();

	PRINTF(PrintColor::Red, "delete %s", GetName());

	delete this;
}

void Tank::InitSprite()
{
	Up->CreateSprite();
	Up->EnableTick();

	Down->CreateSprite();
	Down->EnableTick();

	Right->CreateSprite();
	Right->EnableTick();

	Left->CreateSprite();
	Left->EnableTick();

	SetSize(Left->GetSize());
}

Tank* Tank::SpawnTankBasic(TankSpawnPoint SpawnPoint, bool bInitialize)
{
	SpriteFlipFlop* Left = new SpriteFlipFlop(TANK_LEFT_0, TANK_LEFT_1);
	SpriteFlipFlop* Right = new SpriteFlipFlop(TANK_RIGHT_0, TANK_RIGHT_1);
	SpriteFlipFlop* Up = new SpriteFlipFlop(TANK_UP_0, TANK_UP_1);
	SpriteFlipFlop* Down = new SpriteFlipFlop(TANK_DOWN_0, TANK_DOWN_1);

	// hack to get tank to set anchor before Initialization
	VecInt2D TankSize(TANK_W, TANK_H);

	VecInt2D TankSpawnPosition = SpawnPoint.SpawnPosition - GetAnchorOffset(TankSize, SpawnPoint.SpawnAnchor);

	Tank* SpawnedTank = new Tank(Left, Right, Up, Down, TankSpawnPosition, SpawnPoint.SpawnDirection,
		TANK_HEALTH_BASIC, TANK_SPEED_SLOW, TANK_SPEED_SLOW_ANIM_TIME);

	std::string Name = "tank_basic_" + std::to_string(TankCount);
	SpawnedTank->SetName(Name);

	if (bInitialize)
	{
		SpawnedTank->Initialize();
	}

	TankCount++;

	return SpawnedTank;
}

Tank* Tank::SpawnEnemyTankBasic(TankSpawnPoint SpawnPoint, bool bInitialize)
{
	SpriteFlipFlop* Left = new SpriteFlipFlop(TANK_EB_LEFT_0, TANK_EB_LEFT_1);
	SpriteFlipFlop* Right = new SpriteFlipFlop(TANK_EB_RIGHT_0, TANK_EB_RIGHT_1);
	SpriteFlipFlop* Up = new SpriteFlipFlop(TANK_EB_UP_0, TANK_EB_UP_1);
	SpriteFlipFlop* Down = new SpriteFlipFlop(TANK_EB_DOWN_0, TANK_EB_DOWN_1);

	// hack to get tank to set anchor before Initialization
	VecInt2D TankSize(TANK_W, TANK_H);

	VecInt2D TankSpawnPosition = SpawnPoint.SpawnPosition - GetAnchorOffset(TankSize, SpawnPoint.SpawnAnchor);

	Tank* SpawnedTank = new Tank(Left, Right, Up, Down, TankSpawnPosition, SpawnPoint.SpawnDirection,
		TANK_HEALTH_BASIC, TANK_SPEED_SLOW, TANK_SPEED_SLOW_ANIM_TIME);
	
	std::string Name = "tank_enemy_basic_" + std::to_string(TankCount);
	SpawnedTank->SetName(Name);

	if (bInitialize)
	{
		SpawnedTank->Initialize();
	}

	TankCount++;

	PRINTF(PrintColor::Green, "%s spawned at X=%d Y=%d", SpawnedTank->GetName(), TankSpawnPosition.X, TankSpawnPosition.Y);

	return SpawnedTank;
}

void Tank::Respawn(TankSpawnPoint RespawnPoint)
{
	VecInt2D RespawnPosition = RespawnPoint.SpawnPosition - GetAnchorOffset(Size, RespawnPoint.SpawnAnchor);

	SetPosition(RespawnPosition);
	SetNextDirectionSprite(RespawnPoint.SpawnDirection);
	ChangeCurrentDirectionSprite();
	SetHealth(GetBaseHealth(), true);
	
	if (RESPAWN_PROTECTION_TIME > 0)
	{
		PRINTF(PrintColor::Blue, "%s respawn protection %d ms", GetName(), RESPAWN_PROTECTION_TIME);
		EnableFlashyEffect(RESPAWN_PROTECTION_TIME);
	}
}

void Tank::EnableFlashyEffect(unsigned int FlashyTime)
{
	if (!bFlashyEffectCreated)
	{
		FlashyEffect = CreateDefaultFlashyEffect(Position);
		bFlashyEffectCreated = true;
	}
	bFlashyEffectEnabled = true;
	FlashyEffectTimer = FlashyTime;
}

void Tank::DisableFlashyEffect()
{
	bFlashyEffectEnabled = false;
}

SpriteFlipFlop* Tank::CreateDefaultFlashyEffect(VecInt2D Position)
{
	SpriteFlipFlop* FlashyEffect = new SpriteFlipFlop(FLASHY_0, FLASHY_1, FLASHY_ANIM_TIME);
	
	FlashyEffect->SetPosition(Position);
	FlashyEffect->CreateSprite();
	FlashyEffect->EnableTick();

	return FlashyEffect;
}
