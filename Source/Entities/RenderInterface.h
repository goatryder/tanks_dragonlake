#pragma once

#include "Structs/VecInt2D.h"
#include "Framework.h"
#include "GlobalConstants.h"


enum class Anchor
{
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_DOWN,
	CENTER
};

VecInt2D GetAnchorOffset(VecInt2D Size, Anchor Anchor);


class RenderInterface
{

public:

	RenderInterface() {}
	~RenderInterface() {}

	virtual void onRender() = 0;

	const VecInt2D GetPosition()
	{
		return Position;
	}

	/** if Check bounds, then object will be forced to have position inside game bounds only */
	void SetPosition(VecInt2D NewPosition, bool bCheckBounds = false)
	{
		if (bCheckBounds)
		{
			SetPositionBoundClamped(NewPosition);
		}
		else 
		{
			this->Position = NewPosition;
		}
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

	bool CheckCollision(RenderInterface* Other)
	{
		if (Other == nullptr)
		{
			return false;
		}

		VecInt2D DeltaPos = (Position - Other->GetPosition()).GetAbs();
		VecInt2D MaxSize = VecInt2D::GetMax(Size, Other->GetSize());

		if (DeltaPos.X >= MaxSize.X || DeltaPos.Y >= MaxSize.Y)
		{
			return false;
		}

		return true;
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

protected:

	bool bEnabled = true;
	VecInt2D Size;
	VecInt2D Position;

	void InitSizeBySprite(Sprite* SpriteObj)
	{
		if (SpriteObj == nullptr)
			return;

		int w, h;
		getSpriteSize(SpriteObj, w, h);
		Size = VecInt2D(w, h);
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