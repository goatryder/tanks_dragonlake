#pragma once

#include "Structs/VecInt2D.h"
#include "Framework.h"

class RenderInterface
{

public:

	RenderInterface() {}
	~RenderInterface() {}

	const VecInt2D GetPosition()
	{
		return Position;
	}

	void SetPosition(VecInt2D Position)
	{
		this->Position = Position;
	}

	bool GetEnable()
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

	virtual void onRender() = 0;

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
};