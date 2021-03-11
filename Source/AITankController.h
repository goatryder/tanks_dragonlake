#pragma once

#include <map>

class Tank;
class Phoenix;
struct CollisionCheckResult;

class GameMode;

struct TankCollectiveBrain
{
	Tank* PlayerTank = nullptr;
	Phoenix* PlayerBase = nullptr;

	TankCollectiveBrain() {}
	TankCollectiveBrain(Tank* PlayerTank, Phoenix* PlayerBase) : PlayerTank(PlayerTank), PlayerBase(PlayerBase) {}
};

struct TankBrain
{
	Tank* BrainOwner = nullptr;

	unsigned int TimeSinseLastShot = 0;
	
	unsigned int TimeSinseDirectionChange = 0;
	
	unsigned int TimeSinseLastCollide = 0;

	CollisionCheckResult* LastPostiveCollidedResult = nullptr;

	static int FireRateMin;
	static int FireRateMax;

	static int ChangeDirectionTimeMin;
	static int ChangeDirectionTimeMax;

	TankBrain() {}
	TankBrain(Tank* BrainOwner) : BrainOwner(BrainOwner) {}
	~TankBrain() { delete LastPostiveCollidedResult; }

};

/**
 * A* Alghorithm... JK
 */
class AITankController
{
public:
	AITankController() {}
	AITankController(Tank* PlayerTank, Phoenix* PlayerBase, GameMode* GameModeOwner); 
	~AITankController() {}
	
	TankCollectiveBrain CollectiveBrain;

	std::map<Tank*, TankBrain> AIControlledTankBrains = {};

	GameMode* GameModeOwner = nullptr;

	/** Update Collective Brain*/
	void RefreshCollectiveBrain();
	
	/** Update each unique brain */
	void RefreshTankBrains(unsigned int DeltaTime);

	/** Calc Move() of Fire() for each Tank in AIControlledTanks vector */
	void UpdateTanksBehavior(unsigned int DeltaTime);

	/** Tanks will spawn dynamically, method for adding tank to AIControlledTanks */
	void AddTank(Tank* TankToAddControl)
	{
		if (TankToAddControl == nullptr) return;

		TankBrain Brain(TankToAddControl);
		AIControlledTankBrains.insert(std::pair<Tank*, TankBrain>(TankToAddControl, Brain));
	}

	void RemoveTank(Tank* TankToReleaseControl)
	{
		std::map<Tank*, TankBrain>::iterator Iter;

		Iter = AIControlledTankBrains.find(TankToReleaseControl);
		AIControlledTankBrains.erase(Iter);
	}

	/** For now it's should be synchronized with game tick */
	void onTick(unsigned int DeltaTime)
	{
		RefreshCollectiveBrain();
		RefreshTankBrains(DeltaTime);
		UpdateTanksBehavior(DeltaTime);
	}
};