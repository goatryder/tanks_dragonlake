#pragma once

#include "../Entities/RenderBase.h"
#include <array>

class BrickBase;

#define BrickArrSize 16
#define BrickArrRowSize 4

typedef std::array<BrickBase*, BrickArrSize> brickArr;


class BrickBlock : public RenderBase
{
public:

	BrickBlock(brickArr BrickArray, VecInt2D Position);
	~BrickBlock() {}

private:

	brickArr BrickArray;
	int BricksToDestroyNum;

public:

	virtual void onRender() override final;
	virtual void Initialize() override final;
	virtual void Destroy() override final;

	/* set to null in array */
	void OwnedBrickDestroyed(int Index);

	/* replicate damage to other columns/rows */
	void OwnedBrickDamaged(int Index, int Damage, Direction Side);

	/** spawn brick block with all 16 pieces */
	static BrickBlock* SpawnBrickBlockSolid(VecInt2D Position, bool bInitialize = false);
	static int BlockCount;
};