#include "CountSpriteUI.h"

#include "Entities/SpriteEntity.h"

void CountSpriteUI::onRender()
{
	if (SpriteObj == nullptr) return;
	if (MaxNum == 0) return;
	if (!bEnabled) return;

	for (int i = 0; i < CurrentNum; i++)
	{
		VecInt2D DrawPosition = DrawFirstPosition;
		DrawPosition.X += (i % MaxHorizontalNum) * DrawOffset.X;
		DrawPosition.Y += (i / MaxHorizontalNum) * DrawOffset.Y;

		SpriteObj->DrawAtPosition(DrawPosition);
	}
}

CountSpriteUI* CountSpriteUI::CreateCountSpriteUI(const char* ResourcePath, VecInt2D DrawFirstPosition, VecInt2D DrawOffset, 
	int InitialNum, int MaxHorizontalNum, int MaxNum)
{
	SpriteEntity* SpriteObj = SpriteEntity::SpawnBasicSprite(ResourcePath, DrawFirstPosition);

	return new CountSpriteUI(SpriteObj, DrawFirstPosition, DrawOffset, InitialNum, MaxHorizontalNum, MaxNum);
}
