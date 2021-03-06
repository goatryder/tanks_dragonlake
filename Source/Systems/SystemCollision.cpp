#include "SystemCollision.h"

#include "../Entities/RenderBase.h"

// #include "../Helpers/DebugPrint.h"

// Initialize CollidableSet
std::set<RenderBase*> SystemCollision::CollidableSet = {};

// Initilize Default CollisionCheckResult Out
CollisionCheckResult CollisionCheckResult::DefaultResultOut;

// has nice perfomance, ToDo: figure out how to make it global
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

	// traverse unique pairs loop
	for (Iter = CollidableSet.begin(); std::next(Iter) != CollidableSet.end(); Iter++)
	{
		CollidableFirst = *(Iter);

		Jiter = Iter;
		Jiter++;

		for (Jiter; Jiter != CollidableSet.end(); Jiter++)
		{
			CollidableSecond = *(Jiter);

			if (!CollidableFirst->IsInCollisionIgnore(CollidableSecond, true))  // process ignore list filter
			{
				if (CollidableFirst->IsCollidingWith(CollidableFirst->GetPosition(true), CollidableSecond, CollidableSecond->GetPosition(true)))
				{
					CollidableFirst->onCollide(CollidableSecond, CollisionFilter::CF_BLOCK);
					CollidableFirst->LastCollisionResult.bCollided = true;
					CollidableFirst->LastCollisionResult.LastCollided = CollidableSecond;

					// todo fix exception
					CollidableSecond->onCollide(CollidableFirst, CollisionFilter::CF_BLOCK);
					CollidableSecond->LastCollisionResult.bCollided = true;
					CollidableSecond->LastCollisionResult.LastCollided = CollidableFirst;
				}
			}
		}
	}

	// handle sweep
	for (Iter = CollidableSet.begin(); Iter != CollidableSet.end(); Iter++)
	{
		CollidableFirst = *(Iter);

		if (CollidableFirst->bNextPositionRelevent)
		{
			VecInt2D Pos = CollidableFirst->GetPosition();
			VecInt2D NewPos = CollidableFirst->NextPosition;

			//PRINTF(PrintColor::Blue, "\tSweep: %s last x=%d y=%d new x=%d y=%d", CollidableFirst->GetName(),
			//	Pos.X, Pos.Y, NewPos.X, NewPos.Y);

			CollidableFirst->HandleSweepPosition(CollidableFirst->NextPosition, 
				CollidableFirst->LastCollisionResult);

			CollidableFirst->bNextPositionRelevent = false;
		}
	}

	/*
	// debug print result test failed, somewhere lastcollision result setted to null
	PRINT(PrintColor::Blue, "result CheckCollisionsAllBlock():");

	for (Iter = CollidableSet.begin(); Iter != CollidableSet.end(); Iter++)
	{
		CollidableFirst = *(Iter);

		const char* Name = CollidableFirst->GetName();
		const char* OtherName;
		const char* IsCollided;

		if (CollidableFirst->LastCollisionResult.bCollided)
		{
			OtherName = CollidableFirst->LastCollisionResult.LastCollided->GetName();
			IsCollided = "true";
		}
		else
		{
			OtherName = "NONE";
			IsCollided = "false";
		}

		PRINTF(PrintColor::Blue, "\t%s collided: %s last collided: %s", Name, OtherName, IsCollided);
	}*/
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

		if (PossiblyCollided == Collidable || Collidable->IsInCollisionIgnore(PossiblyCollided))  // process ignore list
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
