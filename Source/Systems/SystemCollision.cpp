#include "SystemCollision.h"

#include "../Entities/RenderBase.h"

// Initialize CollidableSet
std::set<RenderBase*> SystemCollision::CollidableSet = {};

void SystemCollision::CheckCollisions()
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

			if (CollidableFirst->IsCollidingWith(CollidableSecond))
			{
				CollidableFirst->onCollide(CollidableSecond);
				CollidableSecond->onCollide(CollidableFirst);
			}
		}
	}
}
