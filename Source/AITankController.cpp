#include "AITankController.h"

#include "GameMode.h"


int TankBrain::FireRateMin = ENEMY_TANK_SLOW_FIRE_RATE_MIN;
int TankBrain::FireRateMax = ENEMY_TANK_SLOW_FIRE_RATE_MAX;

int TankBrain::ChangeDirectionTimeMin = ENEMY_TANK_CHANGE_DIRECTION_MIN;
int TankBrain::ChangeDirectionTimeMax = ENEMY_TANK_CHANGE_DIRECTION_MIN;

AITankController::AITankController(Tank* PlayerTank, Phoenix* PlayerBase, GameMode* GameModeOwner)
	: GameModeOwner(GameModeOwner)
{
	CollectiveBrain = TankCollectiveBrain(PlayerTank, PlayerBase);
}


void AITankController::RefreshCollectiveBrain()
{
	if (GameModeOwner == nullptr)
	{
		return;
	}

	CollectiveBrain.PlayerTank = GameModeOwner->GetPlayerTank();
	CollectiveBrain.PlayerBase = GameModeOwner->GetPhoenix();
}

void AITankController::RefreshTankBrains(unsigned int DeltaTime)
{
	/*void RefreshBrain(unsigned int DeltaTime, CollisionCheckResult& NewLastPositibeCollidedResult, bool bCollisionUpdate)
{
	
	TimeSinseLastShot += DeltaTime;
	TimeSinseDirectionChange += DeltaTime;

	if (bCollisionUpdate)
	{
		// LastPostiveCollidedResult->~CollisionCheckResult();
		new (LastPostiveCollidedResult) CollisionCheckResult(NewLastPositibeCollidedResult);

		TimeSinseLastCollide = 0;
	}
	else
	{
		TimeSinseLastCollide += DeltaTime;
	}

}*/
}

void AITankController::UpdateTanksBehavior(unsigned int DeltaTime)
{
	if (GameModeOwner == nullptr)
	{
		return;
	}

	Tank* PlayerTank = GameModeOwner->GetPlayerTank();

	/*
	CollectiveBrain.RefreshBrain(PlayerTank);

	for (auto const& Pair : AIControlledTankBrains)
	{
		Tank* Tank = Pair.first;

		if (Tank == nullptr) continue;

		TankBrain Brain = Pair.second;

		bool bShouldUpdateCollision = Tank->LastCollisionResult.bCollided;

		Brain.RefreshBrain(DeltaTime, Tank->LastCollisionResult, bShouldUpdateCollision);
	}*/
}


