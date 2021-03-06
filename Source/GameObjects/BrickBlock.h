#pragma once

#include "../Entities/RenderBase.h"

class BrickBase;

class BrickBlock : public RenderBase
{
public:
	BrickBlock(BrickBase* BrickArray[4][4], VecInt2D Position);
	~BrickBlock() {}

public:

	BrickBase* BrickArray[4][4];

	virtual void onRender() override;
	virtual void onDestroy() override;

	/* set to null in array */
	void OwnedBrickDestroyed(int Index);

	/* replicate damage to other columns/rows */
	void OwnedBrickDamaged(int Index, int Damage, Direction Side);

	/** spawn brick block with all 16 pieces */
	// static BrickBlock* SpawnBrickBlockSolid(VecInt2D Position, bool bSetRenderEnable = true);
};