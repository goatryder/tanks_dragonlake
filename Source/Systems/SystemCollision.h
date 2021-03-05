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

	static CollisionCheckResult DefaultResultOut;
};

/*
 * This static class handles collision for instances inherited from RenderBase
 * in main method CheckCollisionsAllOverlap() there loop which check if unique pair of Objects Collides and call onCollide() for each;
 * Can check collision for separate instances in CheckCollision(Filter);
 */
class SystemCollision
{
protected:

	static std::set<RenderBase*> CollidableSet;

public:

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

	/* get collidable set */
	static const std::set<RenderBase*>& GetCollidableSet()
	{
		return CollidableSet;
	}

	/** calls onCollide() for each unique pair of objects that collides with overlap filter. */
	static void CheckCollisionsAllOverlap();

	/** calls onCollide() for each collided object */
	static void CheckCollision(RenderBase* Collidable, VecInt2D CollidablePosition, CollisionFilter Filter, 
		CollisionCheckResult &ResultOut = CollisionCheckResult::DefaultResultOut);
};