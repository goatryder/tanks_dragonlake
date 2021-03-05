#include "SystemCollision.h"

#include "../Entities/RenderBase.h"

// Initialize CollidableSet
std::set<RenderBase*> SystemCollision::CollidableSet = {};

// Initilize Default CollisionCheckResult Out
CollisionCheckResult CollisionCheckResult::DefaultResultOut;

// has nice perfomance, ToDo: figure out how to make it global
void SystemCollision::CheckCollisionsAllOverlap()
{
	std::set<RenderBase*>::iterator Iter;
	std::set<RenderBase*>::iterator Jiter;

	// traverse unique pairs loop
	for (Iter = CollidableSet.begin(); Iter != CollidableSet.end(); Iter++)
	{
		RenderBase* CollidableFirst = *(Iter);
		
		Jiter = Iter;
		Jiter++;

		for (Jiter; Jiter != CollidableSet.end(); Jiter++)
		{
			RenderBase* CollidableSecond = *(Jiter);

			if (CollidableFirst->IsCollidingWith(CollidableFirst->GetPosition(), CollidableSecond))
			{
				CollidableFirst->onCollide(CollidableSecond, CollisionFilter::CF_OVERLAP);
				CollidableSecond->onCollide(CollidableFirst, CollisionFilter::CF_OVERLAP);
			}
		}
	}
}

void SystemCollision::CheckCollision(RenderBase* Collidable, VecInt2D CollidablePositon, 
	CollisionFilter Filter, CollisionCheckResult &ResultOut)
{
	std::set<RenderBase*>::iterator Iter;

	RenderBase* PossiblyCollided = nullptr;
	RenderBase* LastCollided = nullptr;
	
	bool bCollided = false;

	for (Iter = CollidableSet.begin(); Iter != CollidableSet.end(); Iter++)
	{
		PossiblyCollided = *(Iter);

		if (PossiblyCollided == Collidable || Collidable->IsInCollisionIgnore(PossiblyCollided))  // process ignore list
		{
			continue;
		}

		if (Collidable->IsCollidingWith(CollidablePositon, PossiblyCollided))
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
