#pragma once

#include "../Entities/TickInterface.h"
#include "../Entities/RenderBase.h"
#include "HealthInterface.h"

class SpriteFlipFlop;

class Bullet;

struct LevelStruct;

struct TankSpawnPoint
{
	VecInt2D SpawnPosition;
	Direction SpawnDirection = Direction::UP;
	Anchor SpawnAnchor = Anchor::TOP_LEFT;

	TankSpawnPoint() {}

	TankSpawnPoint(VecInt2D Position, Direction Direction, Anchor Anchor)
		: SpawnPosition(Position), SpawnDirection(Direction), SpawnAnchor(Anchor) {}

	static TankSpawnPoint TopLeftSpawnPoint;
	static TankSpawnPoint TopRightSpawnPoint;
	static TankSpawnPoint BottomLeftSpawnPoint;
	static TankSpawnPoint BottomRightSpawnPoint;
	static TankSpawnPoint TopCenterSpawnPoint;
};

class Tank : public RenderBase, public TickInterface, public HealthInterface
{
public:

	Tank(SpriteFlipFlop* Left, SpriteFlipFlop* Right, SpriteFlipFlop* Up, SpriteFlipFlop* Down,
		VecInt2D Position, Direction Direction, int Health, int Speed, int MoveAnimSpeed);
	~Tank();

	int Speed;

	// only one active bullet for player tank allowed
	Bullet* ActiveBullet = nullptr;

protected:

	// direction
	SpriteFlipFlop* Left;
	SpriteFlipFlop* Right;
	SpriteFlipFlop* Up;
	SpriteFlipFlop* Down;

	Direction CurrentDirection;
	SpriteFlipFlop* CurrentActiveSprite;

	Direction NextDirection;
	SpriteFlipFlop* NextActiveSprite;

	void ChangeCurrentDirectionSprite();
	void SetNextDirectionSprite(Direction DirectionTo);

	bool bCanMove = false;

	// movement
	void Move(unsigned int DeltaTime);

	// movement anim
	int MoveAnimSpeed;

	void PlayMoveAnim();
	void StopMoveAnim();

	bool bPossessedByPlayer = false;

public:

	void MoveBegin(Direction DirectionTo);
	void MoveEnd(Direction DirectionTo);

	void Fire();

	Direction GetDirection() const { return CurrentDirection; }

	virtual void onDamage(int Damage, Direction From) override final;
	virtual void onDead() override final;

	virtual void onTick(unsigned int DeltaTime) override final;

	virtual void onRender() override final;
	virtual void onCollide(RenderBase* Other, CollisionFilter Filter) override final;
	virtual void Initialize() override final;
	virtual void Destroy() override final;

	void InitSprite();

public:

	static int TankCount;
	static Tank* SpawnTankBasic(TankSpawnPoint SpawnPoint, bool bInitialize = false);
	static Tank* SpawnEnemyTankBasic(TankSpawnPoint SpawnPoint, bool bInitialize = false);

	void Respawn(TankSpawnPoint RespawnPoint);

public:
	/** if value > 0, can't damage tank */
	int FlashyEffectTimer = 0;

	SpriteFlipFlop* FlashyEffect = nullptr;

	/** enable tank flashy effect, if time == 0 -> permanent flashy */
	void EnableFlashyEffect(unsigned int FlashyTime);
	void DisableFlashyEffect();
	
	static SpriteFlipFlop* CreateDefaultFlashyEffect(VecInt2D Position);

	bool bDropPickableOnDeath = false;
};