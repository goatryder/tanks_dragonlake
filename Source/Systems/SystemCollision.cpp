#include "SystemCollision.h"

#include "../Entities/RenderBase.h"

// Initialize CollidableSet
std::set<RenderBase*> SystemCollision::CollidableSet = {};

// Initilize Default CollisionCheckResult Out
CollisionCheckResult CollisionCheckResult::DefaultResultOut;

void CollisionCheckResult::UpdateResult(RenderBase* Left, RenderBase* Right)
{
	this->bCollided = true;

	int CollidableDistance = (Left->GetPosition() - Right->GetPosition()).Size();

	if (LastCollided == nullptr || CollidableDistance <= Distance)
	{
		Distance = CollidableDistance;
		LastCollided = Right;
	}
}

// @ToDo: optimize, make one loop if possible
void SystemCollision::CheckCollisionsAllBlock()
{
	std::set<RenderBase*>::iterator Iter;
	std::set<RenderBase*>::iterator Jiter;

	RenderBase* CollidableFirst;
	RenderBase* CollidableSecond;

	// hack to clear prev collision result
	for (Iter = CollidableSet.begin(); Iter != CollidableSet.end(); Iter++)
	{
		(*Iter)->LastCollisionResult = CollisionCheckResult();
	}

	// traverse unique pairs loop and get result
	for (Iter = CollidableSet.begin(); std::next(Iter) != CollidableSet.end(); Iter++)
	{
		CollidableFirst = *(Iter);

		Jiter = Iter;
		Jiter++;

		for (Jiter; Jiter != CollidableSet.end(); Jiter++)
		{
			CollidableSecond = *(Jiter);

			if (CollidableFirst->CanCollideWith(CollidableSecond, true))  // process black/white list filter
			{
				if (CollidableFirst->IsCollidingWith(CollidableFirst->GetPosition(true), CollidableSecond, CollidableSecond->GetPosition(true)))
				{
					CollidableFirst->LastCollisionResult.UpdateResult(CollidableFirst, CollidableSecond);
					CollidableSecond->LastCollisionResult.UpdateResult(CollidableSecond, CollidableFirst);
				}
			}
		}
	}

	// handle result and sweep
	for (Iter = CollidableSet.begin(); Iter != CollidableSet.end(); Iter++)
	{
		CollidableFirst = *(Iter);

		CollisionCheckResult& Result = CollidableFirst->LastCollisionResult;

		if (Result.bCollided)
		{
			CollidableFirst->onCollide(Result.LastCollided, CollisionFilter::CF_BLOCK);
		}

		if (CollidableFirst->bNextPositionRelevent)
		{
			VecInt2D Pos = CollidableFirst->GetPosition();
			VecInt2D NewPos = CollidableFirst->NextPosition;

			CollidableFirst->HandleSweepPosition(CollidableFirst->NextPosition, 
				CollidableFirst->LastCollisionResult);

			CollidableFirst->bNextPositionRelevent = false;
		}
	}
}

// DEPRECATED, NEED TESTING
void SystemCollision::CheckCollision(RenderBase* Collidable, VecInt2D CollidablePositon, 
	CollisionFilter Filter, CollisionCheckResult &ResultOut, bool bCheckNextReleventPos)
{
	std::set<RenderBase*>::iterator Iter;

	RenderBase* PossiblyCollided = nullptr;
	RenderBase* LastCollided = nullptr;

	for (Iter = CollidableSet.begin(); Iter != CollidableSet.end(); Iter++)
	{
		PossiblyCollided = *(Iter);

		if (PossiblyCollided == Collidable || !Collidable->CanCollideWith(PossiblyCollided))  // process ignore list
		{
			continue;
		}

		if (Collidable->IsCollidingWith(CollidablePositon, PossiblyCollided, PossiblyCollided->GetPosition(bCheckNextReleventPos)))
		{
			Collidable->onCollide(PossiblyCollided, Filter);
			PossiblyCollided->onCollide(Collidable, Filter);
			
			LastCollided = PossiblyCollided;
		}
	}

	// result
	if (LastCollided != nullptr)
	{
		ResultOut.bCollided = true;
		ResultOut.LastCollided = LastCollided;
	}
}

void SystemCollision::ClearCheckCollisionSet(bool bDestroy)
{
	if (bDestroy)
	{
		for (auto& TickInterfaceInstance : CollidableSet)
		{
			TickInterfaceInstance->Destroy();
		}
	}

	CollidableSet.clear();
}
