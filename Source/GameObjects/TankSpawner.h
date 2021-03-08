#pragma once

#include "../Entities/TickInterface.h"
#include "../Entities/RenderBase.h"

struct TankSpawnPoint
{
	VecInt2D SpawnPosition;
	Direction SpawnDirection;
	Anchor SpawnAnchor;

	TankSpawnPoint(VecInt2D Position, Direction Direction, Anchor Anchor)
		:  SpawnPosition(Position), SpawnDirection(Direction), SpawnAnchor(Anchor) {}

	static TankSpawnPoint TopLeftSpawnPoint;
	static TankSpawnPoint TopRightSpawnPoint;
	static TankSpawnPoint BottomLeftSpawnPoint;
	static TankSpawnPoint BottomRightSpawnPoint;
};

/**
 * Tank spawner, can have multiple spawn points, and handle them all
 * @ToDo: SpawnPoint as class, need to check if other tank or player tank not on spawn point
 */
class TankSpawner : public RenderBase, public TickInterface
{
public:

	TankSpawner(std::vector<TankSpawnPoint> SpawnPoints, int TankSpawnNumMax, unsigned int SpawnRate);
	~TankSpawner();

protected:

	std::vector<TankSpawnPoint> SpawnPoints;

	unsigned int SpawnRate;
	unsigned int SpawnRateAccomulated;

	int TankSpawnNumMax;
	int TankSpawnNum;

	TankSpawnPoint& ChooseSpawnPoint();
	void SpawnTank(TankSpawnPoint& SpawnPoint);

public:

	virtual void onTick(unsigned int DeltaTime) override final;
	virtual void onRender() override final;
	virtual void Destroy() override final;
	virtual void Initialize() override final;
	
	static int SpawnerCount;
	static TankSpawner* CreateBasicTankSpawnerCorners(bool Initialize = false);
};