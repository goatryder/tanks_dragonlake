#pragma once
#include <string>

#include "GlobalConstants.h"
#include "Structs/VecInt2D.h"
#include "Framework.h"

#include "../Systems/SystemCollision.h"
#include "../Systems/SystemRender.h"

enum class Anchor
{
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_DOWN,
	CENTER
};

// simplest collision filter, used in setPosition()
enum class CollisionFilter
{
	CF_IGNORE,  // no collision check, set newPosition
	CF_OVERLAP, // set newPosition, calls onCollide(this Filter=Overlap) for overlapped instance
	CF_BLOCK,  // don't set newPosition, calls onCollide(this, Filter=Block) if collided with other instance (can collide with wall).
};

VecInt2D GetAnchorOffset(VecInt2D Size, Anchor Anchor);

class RenderBase
{

public:

	RenderBase() {}
	
	~RenderBase() 
	{
		if (bCollisionEnabled) SystemCollision::RemoveRenderObj(this);
		if (bRenderEnabled) SystemRender::RemoveRenderObj(this);
	}

	virtual void onRender() = 0;
	virtual void onCollide(RenderBase* Other, CollisionFilter Filter) {}

	const VecInt2D GetPosition()
	{
		return Position;
	}

	/** Set Position with Collision */
	void SetPosition(VecInt2D NewPosition, CollisionFilter Filter = CollisionFilter::CF_IGNORE)
	{
		if (Filter == CollisionFilter::CF_BLOCK)
		{
			CollisionCheckResult CollisionResultIn;
			SystemCollision::CheckCollision(this, NewPosition, CollisionFilter::CF_BLOCK, CollisionResultIn);

			if (CollisionResultIn.bCollided)
			{
				SetPositionBlockClamped(NewPosition, CollisionResultIn.LastCollided);
				return;
			}

			if (!IsPositionInGameBound(NewPosition))
			{
				SetPositionBoundClamped(NewPosition);
				return;
			}

		}
		else if (Filter == CollisionFilter::CF_OVERLAP)
		{
			SystemCollision::CheckCollision(this, NewPosition, CollisionFilter::CF_OVERLAP);
		}
		
		Position = NewPosition;
	}

	bool IsEnabled()
	{
		return bEnabled;
	}

	void SetEnable(bool bEnable)
	{
		bEnabled = bEnable;
	}

	const VecInt2D GetSize()
	{
		return Size;
	}

	void SetSize(VecInt2D Size)
	{
		this->Size = Size;
	}

	bool IsCollidingWith(VecInt2D Position, RenderBase* Other)
	{
		if (Other == nullptr)
		{
			return false;
		}

		VecInt2D OtherPos = Other->GetPosition();
		VecInt2D OtherSize = Other->GetSize();

		if (Position.X < OtherPos.X + OtherSize.X && Position.X + Size.X > OtherPos.X &&
			Position.Y < OtherPos.Y + OtherSize.Y && Position.Y + Size.Y > OtherPos.Y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool IsPositionInGameBound(VecInt2D NewPosition)
	{
		if (NewPosition.X < GAME_AREA_W0) return false;

		if (NewPosition.X + Size.X > GAME_AREA_W1) return false;

		if (NewPosition.Y < GAME_AREA_H0) return false;

		if (NewPosition.Y + Size.Y > GAME_AREA_H1) return false;

		return true;
	}

	/** Get center offset, Offset = Size / 2 */
	VecInt2D GetCenterOffset()
	{
		return Size / 2;
	}

	/** Get center position of Render instance, CenterPos = Position + CenterOffset */
	VecInt2D GetCenterPosition()
	{
		return Position + GetCenterOffset();
	}

	/** Get offset of Side */
	VecInt2D GetSideOffset(Direction Side)
	{
		VecInt2D SideOffset;

		switch (Side)
		{
		case Direction::RIGHT:
			SideOffset.X = Size.X / 2;
			break;
		case Direction::LEFT:
			SideOffset.X = -Size.X / 2;
			break;
		case Direction::DOWN:
			SideOffset.Y = Size.Y / 2;
			break;
		default:
			SideOffset.Y = -Size.Y / 2;
			break;
		}

		return SideOffset;
	}

	/** Get center point of chosen bounding box line, SidePos = CenterPos + SideOffset */
	VecInt2D GetSidePosition(Direction Side)
	{
		return GetCenterPosition() + GetSideOffset(Side);
	}

	/** Get center point of opposite chosen bounding box line, OppositeSidePos = CenterPos - SideOffset */
	VecInt2D GetOppositeSidePosition(Direction Side)
	{
		return  GetCenterPosition() - GetSideOffset(Side);
	}

	void EnableCollsion()
	{
		SystemCollision::AddRenderObj(this);
		bCollisionEnabled = true;
	}

	void DisableCollision()
	{
		SystemCollision::RemoveRenderObj(this);
		bCollisionEnabled = false;
	}

	bool IsCollisionEnabled() 
	{ 
		return bCollisionEnabled; 
	}
	
	void EnableRender() 
	{
		SystemRender::AddRenderObj(this);
	}

	void DisableRender()
	{
		SystemRender::RemoveRenderObj(this);
	}

	bool IsRenderEnabled() 
	{ 
		return bRenderEnabled; 
	}

	const char* GetName()
	{
		return Name.c_str();
	}

	void SetName(std::string NewName)
	{
		Name = NewName;
	}

	/** Check if Collidable in CollisionIgnored list */
	bool IsInCollisionIgnore(RenderBase* Collidable, bool bCheckOtherIgonreList = false)
	{
		std::vector<RenderBase*>::iterator Iter;
		Iter = std::find(CollisionIgnored.begin(), CollisionIgnored.end(), Collidable);
		
		bool bCollidableIgnored = Iter != CollisionIgnored.end();

		if (bCheckOtherIgonreList)
		{
			bCollidableIgnored = bCollidableIgnored || Collidable->IsInCollisionIgnore(this, false);
		}
		
		return bCollidableIgnored;
	}

	void AddCollidableToIgnore(RenderBase* Collidable)
	{
		CollisionIgnored.push_back(Collidable);
	}

	void RemoveCollidableFromIgnore(RenderBase* Collidable)
	{
		std::vector<RenderBase*>::iterator Iter;
		Iter = std::find(CollisionIgnored.begin(), CollisionIgnored.end(), Collidable);

		if (Iter != CollisionIgnored.end())
		{
			CollisionIgnored.erase(Iter);
		}
	}

	std::vector<RenderBase*> CollisionIgnored;

protected:

	bool bEnabled = true;
	VecInt2D Size;
	VecInt2D Position;

	std::string Name;

	bool bCollisionEnabled = false;
	bool bRenderEnabled = false;

	void InitSizeBySprite(Sprite* SpriteObj)
	{
		if (SpriteObj == nullptr)
			return;

		int w, h;
		getSpriteSize(SpriteObj, w, h);
		Size = VecInt2D(w, h);
	}

	void SetPositionBlockClamped(VecInt2D NewPosition, RenderBase* Blocker)
	{
		VecInt2D Delta_Pos = NewPosition - Position;
		
		VecInt2D BlockerSize = Blocker->Size;
		
		VecInt2D BlockerPos = Blocker->Position;

		if (Delta_Pos.X > 0) // NewPosition is on the right side from old Position and on left from blocker
		{
			NewPosition.X = BlockerPos.X - Size.X; // Set to Blocker Left Side X
		}
		else if (Delta_Pos.X < 0)
		{
			NewPosition.X = BlockerPos.X + BlockerSize.X; // Set to Blocker Right Side X
		}
		else if (Delta_Pos.Y > 0) // NewPosition is on the buttom from old Position and on top of blocker
		{
			NewPosition.Y = BlockerPos.Y - Size.Y;  // Set to Blocker Top Y
		}
		else if (Delta_Pos.Y < 0)
		{
			NewPosition.Y = BlockerPos.Y + BlockerSize.Y;  // Set to Blocker Bottom Y
		}
		else
		{
			return;
		}

		// set new position
		Position = NewPosition;
	}

	void SetPositionBoundClamped(VecInt2D NewPosition)
	{
		// clamp x
		if (NewPosition.X < GAME_AREA_W0) 
		{ 
			NewPosition.X = GAME_AREA_W0;
		}
		else if (NewPosition.X + Size.X > GAME_AREA_W1) 
		{
			NewPosition.X = GAME_AREA_W1 - Size.X;
		}

		// clamp y
		if (NewPosition.Y < GAME_AREA_H0) 
		{ 
			NewPosition.Y = GAME_AREA_H0;
		}
		else if (NewPosition.Y + Size.Y > GAME_AREA_H1) 
		{
			NewPosition.Y = GAME_AREA_H1 - Size.Y;
		}

		// set new position
		Position = NewPosition;
	}
};