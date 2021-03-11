#include "AITankController.h"

#include "GameMode.h"

#include "Helpers/DebugPrint.h"

int TankBrain::FireRate = ENEMY_TANK_SLOW_FIRE_RATE;
int TankBrain::ChangeDirectionTime = ENEMY_TANK_CHANGE_DIRECTION_RATE;

AITankController::AITankController(Tank* PlayerTank, Phoenix* PlayerBase, GameMode* GameModeOwner)
	: GameModeOwner(GameModeOwner)
{
	CollectiveBrain = TankCollectiveBrain(PlayerTank, PlayerBase);
}

void AITankController::UpdateTanksBehavior(unsigned int DeltaTime)
{
	// Refresh Collective Brain
	CollectiveBrain.PlayerTank = GameModeOwner->GetPlayerTank();
	CollectiveBrain.PlayerBase = GameModeOwner->GetPhoenix();
	
	for (auto& Pair : AIControlledTankBrains)
	{
		Tank* Tank = Pair.first;
		TankBrain& Brain = Pair.second;

		// Refresh Tanks Brain

		Brain.TimeSinseLastShot += DeltaTime;
		Brain.TimeSinseDirectionChange += DeltaTime;
		Brain.TimeSinseLastCollide += DeltaTime;

		//PRINTF(PrintColor::Yellow, "shot time %d, dir time %d, collide time %d", 
		//	Brain.TimeSinseLastShot, Brain.TimeSinseDirectionChange, Brain.TimeSinseLastCollide);

		CollisionCheckResult& LastCollisionResult = Tank->LastCollisionResult;
		if (LastCollisionResult.bCollided)
		{
			//PRINTF(PrintColor::Yellow, "%s collided with %s", Tank->GetName(), LastCollisionResult.LastCollided->GetName());

			if (Brain.LastPostiveCollidedResult == nullptr)
			{
				Brain.LastPostiveCollidedResult = new CollisionCheckResult(LastCollisionResult);
			}
			else
			{
				Brain.LastPostiveCollidedResult->~CollisionCheckResult();
				new (Brain.LastPostiveCollidedResult) CollisionCheckResult(LastCollisionResult);
			}

			Brain.TimeSinseLastCollide = 0;
			Tank->MoveEnd(Tank->GetDirection());
			
			Direction NewDirection = GetRandomDirection();
			
			while (NewDirection == Brain.LastDirection)
				NewDirection = GetRandomDirection();
			
			Brain.LastDirection = NewDirection;

			Tank->MoveBegin(GetRandomDirection());
		}

		// Update Action
		
		if (Brain.TimeSinseDirectionChange >= Brain.FireRate)
		{
			Tank->MoveBegin(GetRandomDirection());
			Brain.TimeSinseDirectionChange = 0;
		}
		
		if (Brain.TimeSinseLastShot >= Brain.FireRate)
		{
			Tank->Fire();
			Brain.TimeSinseLastShot = 0;
		}

	}
}


