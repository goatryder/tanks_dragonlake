#include "CountNumUI.h"

#include "Entities/SpriteEntity.h"

// @ToDo: handle destruction
const std::array <SpriteEntity*, 10> CountNumUI::SpriteDigits = {
	new SpriteEntity(UI_NUM_0),
	new SpriteEntity(UI_NUM_1),
	new SpriteEntity(UI_NUM_2),
	new SpriteEntity(UI_NUM_3),
	new SpriteEntity(UI_NUM_4),
	new SpriteEntity(UI_NUM_5),
	new SpriteEntity(UI_NUM_6),
	new SpriteEntity(UI_NUM_7),
	new SpriteEntity(UI_NUM_8),
	new SpriteEntity(UI_NUM_9)
};

bool CountNumUI::bSpriteDigitsInitialized = false;

void CountNumUI::onRender()
{
	if (!bEnabled) return;

	for (auto& DigitPos : DigitRenderInfo)
	{
		SpriteDigits[DigitPos.first]->DrawSprite(DigitPos.second);
	}
}

void CountNumUI::Initialize()
{
	// hack to initialize digits sprites
	if (!bSpriteDigitsInitialized)
	{
		bSpriteDigitsInitialized = true;

		for (auto& SpriteObj : SpriteDigits)
		{
			SpriteObj->CreateSprite();
		}
	}
}

inline void CountNumUI::GetDigitsFromValue(Digits& DigitsOut)
{
	int Val = Value;

	while (Val > 0)
	{
		DigitsOut.push_back(Val % 10);
		Val = Val / 10;
	}
}

void CountNumUI::UpdateDigitRenderInfo()
{
	if (MaxSize <= 1)  // value are single digit number
	{
		int Val = Value >= 10 ? 9 : Value % 10;
		DigitPosition DigitPos(Val, DrawFirstPosition);
		DigitRenderInfo = { DigitPos };
		return;
	}

	Digits DigitsIn;
	GetDigitsFromValue(DigitsIn);

	if (DigitsIn.size() > MaxSize)
	{
		DigitsIn = Digits(MaxSize, 9); // value has more digits then max digit number
	}
	else if (DigitsIn.size() < MinSize) // value has less digits them min digit number
	{
		for (int i = 0; i < MinSize - DigitsIn.size(); i++)
		{
			DigitsIn.push_back(0);
		}
	}

	DigitRenderInfo.clear();

	VecInt2D DigitPositionLast = DrawFirstPosition + DrawOffset * (DigitsIn.size() - 1); // digits in vector are in backward order
	DigitPosition DigitPos;

	for (auto& Digit : DigitsIn)
	{
		DigitPos = DigitPosition(Digit, DigitPositionLast);

		DigitRenderInfo.push_back(DigitPos);

		DigitPositionLast -= DrawOffset;
	}
}
