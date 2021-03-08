#include "BrickBlock.h"

#include "BrickBase.h"

#include "../Helpers/DebugPrint.h"

int BrickBlock::BlockCount = 0;


BrickBlock::BrickBlock(brickArr BrickArr, VecInt2D Position)
	: BrickArray(BrickArr)
{
	this->Position = Position;

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

void BrickBlock::Initialize()
{
	for (int i = 0; i < BrickArrSize; i++)
	{
		BrickBase* Brick = BrickArray.at(i);

		if (Brick != nullptr)
		{
			BricksToDestroyNum++; // if cell not empty, increment Brick number to destroy

			Brick->Owner = this;
			Brick->OwnerIndex = i;

			Brick->SpriteInit();
			Brick->EnableCollsion();

			// PRINTF(PrintColor::Yellow, "BrickBlockInit: brick part pos X=%d, Y=%d", Brick->GetPosition().X, Brick->GetPosition().Y);
		}
	}

	// PRINTF(PrintColor::Yellow, "BrickBlockInit: block pos X=%d, Y=%d", Position.X, Position.Y);

	this->Size = BrickArray.at(0)->GetSize() * BrickArrRowSize;  // no need actualy to initialize size, collision use size of SpriteBase from array anyway

	EnableRender();
}

void BrickBlock::Destroy()
{
	RenderBase::Destroy();

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
		Destroy();
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

BrickBlock* BrickBlock::SpawnBrickBlockSolid(VecInt2D Position, bool bInitialize)
{
	std::array<BrickBase*, BrickArrSize>Bricks;

	// hack to spawn brick sprites fragment in chess order
	bool bResourceSwapChessOrder;
	int Even;

	// hack to get brick size
	int BrickBaseSize_X = (GAME_CHUNK_W) / BrickArrRowSize;
	int BrickBaseSize_Y = (GAME_CHUNK_H) / BrickArrRowSize;

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

			// PRINTF(PrintColor::Yellow, "brickSolid: brick part pos X=%d, Y=%d", BrickPosition.X, BrickPosition.Y);

			Bricks.at(Index) = SpawnedBrick;

			BrickPosition.X = Position.X + BrickBaseSize_X * (j + 1);
		}

		BrickPosition.Y = Position.Y + BrickBaseSize_Y * (i + 1);
	}

	BrickBlock* SpawnedBlock = new BrickBlock(Bricks, Position);

	std::string Name = "block_" + std::to_string(BlockCount);
	SpawnedBlock->SetName(Name);

	if (bInitialize)
	{
		SpawnedBlock->Initialize();
	}

	return SpawnedBlock;
}
