#pragma once

#include "BasicUIElement.h"

class CountSpriteUI : public BasicUIElement
{
public:

	CountSpriteUI(SpriteEntity* SpriteObj, VecInt2D DrawFirstPosition, VecInt2D DrawOffset, int InitialNum,
		int MaxHorizontalNum, int MaxNum) : BasicUIElement(SpriteObj), 
		DrawFirstPosition(DrawFirstPosition), DrawOffset(DrawOffset), CurrentNum(InitialNum), 
		MaxHorizontalNum(MaxHorizontalNum), MaxNum(MaxNum) 
	{
		bEnabled = true; // enable by default
	}
	
	~CountSpriteUI() {};

	VecInt2D DrawFirstPosition;
	VecInt2D DrawOffset;
	
	int MaxHorizontalNum;

	int CurrentNum;
	int MaxNum;

	void AddNum(int Num)
	{
		int NewNum = CurrentNum + Num;
		
		if (NewNum > MaxNum)
		{
			CurrentNum = MaxNum;
		}
		else
		{
			CurrentNum = NewNum;
		}
	}

	void SetNum(int Num)
	{
		if (Num > MaxNum)
		{
			CurrentNum = MaxNum;
		}
		else
		{
			CurrentNum = Num;
		}
	}

	virtual void onRender() override final;

	static CountSpriteUI* CreateCountSpriteUI(const char* ResourcePath, VecInt2D DrawFirstPosition,
		VecInt2D DrawOffset, int InitialNum, int MaxHorizontalNum, int MaxNum);

};