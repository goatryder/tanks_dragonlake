#pragma once

#include "../Entities/TickInterface.h"
#include "../Entities/RenderBase.h"

#include <vector>

struct LevelStruct;

struct TankSpawnPoint;

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

	bool TankSpawnerExhausted() { return TankSpawnNum >= TankSpawnNumMax; }

	TankSpawnPoint& ChooseSpawnPoint();
	void SpawnTank(TankSpawnPoint& SpawnPoint);

public:

	virtual void onTick(unsigned int DeltaTime) override final;
	virtual void onRender() override final;
	virtual void Destroy() override final;
	virtual void Initialize() override final;

	static int SpawnerCount;
	static TankSpawner* SpawnBasicTankSpawnerCorners(int SpawnTankNum, int SpawnRate, bool Initialize = false);
};