#include "BrickBlock.h"

#include "BrickBase.h"

#include "../Helpers/DebugPrint.h"

int BrickBlock::BlockCount = 0;


BrickBlock::BrickBlock(brickArr BrickArr, VecInt2D Position)
	: BrickArray(BrickArr)
{
	this->Position = Position;
	this->Size = BrickArr.at(0)->GetSize() * BrickArrRowSize;

	BricksToDestroyNum = 0;

	for (int i = 0; i < BrickArrSize; i++)
	{
		BrickBase* Brick = BrickArray.at(i);

		if (Brick != nullptr)
		{
			BricksToDestroyNum++; // if cell not empty, increment Brick number to destroy

			Brick->Owner = this;
			Brick->OwnerIndex = i;
		}
	}
}

void BrickBlock::onRender()
{
	for (int i = 0; i < BrickArrSize; i++)
	{
		BrickBase* Brick = BrickArray.at(i);

		if (Brick != nullptr)
		{
			Brick->onRender();
		}
	}
}

void BrickBlock::onDestroy()
{
	RenderBase::onDestroy();

	PRINTF(PrintColor::Green, "[block] delete %s", GetName());

	delete this;
}

void BrickBlock::OwnedBrickDestroyed(int Index)
{
	BrickBase*& Brick = BrickArray.at(Index);
	Brick = nullptr;
	
	BricksToDestroyNum--;

	if (BricksToDestroyNum == 0)  // last brick in array destroyed
	{
		onDestroy();
	}
}


void BrickBlock::OwnedBrickDamaged(int Index, int Damage, Direction Side)
{
	int DamagedRow = Index / BrickArrRowSize;
	int DamagedColumn = Index % BrickArrRowSize;

	if (Side == Direction::RIGHT || Side == Direction::LEFT)
	{
		int IndexVertical;

		for (int i = 0; i < BrickArrRowSize; i++)
		{
			IndexVertical = i * BrickArrRowSize + DamagedColumn;
			BrickBase* Brick = BrickArray.at(IndexVertical);

			if (Brick != nullptr)
			{
				Brick->HealthInterface::onDamage(Damage, Side);  // call parent implementation only, avoiding hyperloop
			}
		}
	}
	else
	{
		int IndexHorizontal;

		for (int i = 0; i < BrickArrRowSize; i++)
		{
			IndexHorizontal = DamagedRow * BrickArrRowSize + i;
			BrickBase* Brick = BrickArray.at(IndexHorizontal);

			if (Brick != nullptr)
			{
				Brick->HealthInterface::onDamage(Damage, Side);  // call parent implementation only, avoiding hyperloop
			}
		}
	}
}

BrickBlock* BrickBlock::SpawnBrickBlockSolid(VecInt2D Position, bool bSetRenderEnable)
{
	std::array<BrickBase*, BrickArrSize>Bricks;

	bool bResourceSwapChessOrder;
	int Even;

	BrickBase* SpawnedBrick;
	VecInt2D BrickPosition = Position;
	
	// BrickBase array initialize // todo: handle correct sprites
	for (int i = 0; i < BrickArrRowSize; i++)
	{
		BrickPosition.X = Position.X;
		
		Even = i % 2;

		for (int j = 0; j < BrickArrRowSize; j++)
		{
			int Index = i * BrickArrRowSize + j;

			bResourceSwapChessOrder = (Index + Even) % 2 == 0;

			SpawnedBrick = BrickBase::SpawnBaseBrick(BrickPosition, bResourceSwapChessOrder ? BRICK_0 : BRICK_1, BRICK_BASE_HEALTH, false);

			Bricks.at(Index) = SpawnedBrick;

			BrickPosition.X = Position.X + SpawnedBrick->GetSize().X * (j + 1);
		}

		BrickPosition.Y = Position.Y + SpawnedBrick->GetSize().Y * (i + 1);
	}

	BrickBlock* SpawnedBlock = new BrickBlock(Bricks, Position);

	std::string Name = "block_" + std::to_string(BlockCount);
	SpawnedBlock->SetName(Name);

	if (bSetRenderEnable)
	{
		SpawnedBlock->EnableRender();
	}

	return SpawnedBlock;
}
