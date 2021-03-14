#pragma once

#include "BasicUIElement.h"

#include <vector>
#include <utility>

typedef std::vector<unsigned __int8> Digits; // extra super space optimization
typedef std::pair<unsigned __int8, VecInt2D> DigitPosition;
typedef std::vector<DigitPosition> DigitPosVector;

class CountNumUI : public BasicUIElement
{

public:

	CountNumUI(int InitValue, int MinSize, int MaxSize, VecInt2D DrawFirstPosition, VecInt2D DrawOffset)
		: Value(InitValue), MinSize(MinSize), MaxSize(MaxSize), DrawFirstPosition(DrawFirstPosition), DrawOffset(DrawOffset)
	{
		bEnabled = true; // enable by default
		DigitRenderInfo = {};
		UpdateDigitRenderInfo();
	}

	~CountNumUI()
	{
	};

	VecInt2D DrawFirstPosition;
	VecInt2D DrawOffset;

	int MinSize;
	int MaxSize;


	void AddNum(int Val) { Value += Val; UpdateDigitRenderInfo(); }
	void SetNum(int NewVal) { Value = NewVal; UpdateDigitRenderInfo(); }

	int GetValue() const { return Value; }

	virtual void onRender() override final;
	virtual void Initialize() override final;

protected:

	int Value;

	inline void GetDigitsFromValue(Digits& DigitsOut);

	void UpdateDigitRenderInfo();

	DigitPosVector DigitRenderInfo;

	static bool bSpriteDigitsInitialized;
	static std::vector<SpriteEntity*> SpriteDigits;
	static void InitializeSpriteDigits();

public:

	static CountNumUI* CreateCountNumUI(int InitValue, int MinSize, int MaxSize, VecInt2D DrawFirstPosition, VecInt2D DrawOffset)
	{
		return new CountNumUI(InitValue, MinSize, MaxSize, DrawFirstPosition, DrawOffset);
	}
};