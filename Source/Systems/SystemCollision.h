#pragma once

#include <set>
#include <algorithm>


class RenderBase;
enum class CollisionFilter;
struct VecInt2D;

struct CollisionCheckResult
{
	bool bCollided = false;
	RenderBase* LastCollided = nullptr;
	int Distance = 0;
	static CollisionCheckResult DefaultResultOut;

	/** Updating result, LastCollided will be closest one */
	void UpdateResult(RenderBase* Left, RenderBase* Right);
};

/*
 * This static class handles collision for instances inherited from RenderBase
 * in main method CheckCollisionsAllOverlap() there loop which check if unique pair of Objects Collides and call onCollide() for each;
 * Can check collision for separate instances in CheckCollision(Filter);
 */
class SystemCollision
{
public:

	static std::set<RenderBase*> CollidableSet;

public:

	static SystemCollision& Instance()
	{
		static SystemCollision* Instance = new SystemCollision();
		return *Instance;
	}

	/** add to collision detection set */
	static void AddRenderObj(RenderBase* RenderObj)
	{
		CollidableSet.insert(RenderObj);
	}

	/* remove from collision detection set */
	static void RemoveRenderObj(RenderBase* RenderObj)
	{
		std::set<RenderBase*>::iterator Iter;
		Iter = std::find(CollidableSet.begin(), CollidableSet.end(), RenderObj);

		if (Iter != CollidableSet.end())
		{
			CollidableSet.erase(Iter);
		}
	}

	/** clear collision detection set, can be used on level change */
	static void ClearCheckCollisionSet(bool bDestroy = false);

	/** calls onCollide() for each unique pair of objects that collides with overlap filter. */
	static void CheckCollisionsAllBlock();

	/** DEPRECATED calls onCollide() for each collided object */
	static void CheckCollision(RenderBase* Collidable, VecInt2D CollidablePosition, CollisionFilter Filter, 
		CollisionCheckResult &ResultOut = CollisionCheckResult::DefaultResultOut, bool bCheckNextReleventPos = false);

public:

	SystemCollision() {}
	~SystemCollision() {}
};