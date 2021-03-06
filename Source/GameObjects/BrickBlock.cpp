#include "BrickBlock.h"

#include "BrickBase.h"

#include "../Helpers/DebugPrint.h"

BrickBlock::BrickBlock(BrickBase* BrickArray[4][4], VecInt2D Position)
{
	this->Position = Position;
	this->Size = (**BrickArray)->GetSize() * 4;

	for (int i = 0; i < 16; i++)
	{
		BrickBase* Brick = BrickArray[i >> 2][i % 4];

		if (Brick != nullptr)
		{
			Brick->Owner = this;
			Brick->OwnerIndex = i;
		}
	}
}

void BrickBlock::onRender()
{
	for (int i = 0; i < 16; i++)
	{
		BrickBase* Brick = BrickArray[i >> 2][i % 4];

		if (Brick != nullptr)
		{
			Brick->onRender();
		}
	}
}

void BrickBlock::onDestroy()
{
	for (int i = 0; i < 16; i++)
	{
		BrickBase* Brick = BrickArray[i >> 2][i % 4];
			
		if (Brick != nullptr)
		{
			Brick->onDestroy();
		}
	}

	delete[] BrickArray;
}

void BrickBlock::OwnedBrickDestroyed(int Index)
{
	BrickBase*& Brick = BrickArray[Index >> 2][Index % 4];
	Brick = nullptr;
}

void BrickBlock::OwnedBrickDamaged(int Index, int Damage, Direction Side)
{
	int i = Index >> 2;
	int j = Index % 4;

	if (Side == Direction::DOWN || Side == Direction::LEFT)
	{
		for (i = 0; i < 4; i++)
		{
			BrickBase* Brick = BrickArray[i][j];

			if (Brick != nullptr)
			{
				Brick->HealthInterface::onDamage(Damage, Side);  // call parent implementation only, avoiding hyperloop
			}
		}
	}
	else
	{
		for (j = 0; j < 4; i++)
		{
			BrickBase* Brick = BrickArray[i][j];

			if (Brick != nullptr)
			{
				Brick->HealthInterface::onDamage(Damage, Side);  // call parent implementation only, avoiding hyperloop
			}
		}
	}
}

//BrickBlock* BrickBlock::SpawnBrickBlockSolid(VecInt2D Position, bool bSetRenderEnable)
//{
//	BrickBase* Bricks[4][4];
//
//	int i, j = 0;
//
//	// todo: handle correct sprites
//	for (i; i < 4; i++)
//	{
//		for (j)
//		Bricks[i >> 2][i % 4] = BrickBase::SpawnBaseBrick()
//	}
//
//
//	SpriteFlipFlop* Left = new SpriteFlipFlop(TANK_EB_LEFT_0, TANK_EB_LEFT_1);
//	SpriteFlipFlop* Right = new SpriteFlipFlop(TANK_EB_RIGHT_0, TANK_EB_RIGHT_1);
//	SpriteFlipFlop* Up = new SpriteFlipFlop(TANK_EB_UP_0, TANK_EB_UP_1);
//	SpriteFlipFlop* Down = new SpriteFlipFlop(TANK_EB_DOWN_0, TANK_EB_DOWN_1);
//
//	Position -= GetAnchorOffset(Left->GetSize(), Anchor);
//
//	Tank* SpawnedTank = new Tank(Left, Right, Up, Down, Position, Direction,
//		TANK_HEALTH_BASIC, TANK_SPEED_SLOW, TANK_SPEED_SLOW_ANIM_TIME);
//
//	std::string Name = "tank_enemy_basic_" + std::to_string(TankIndex);
//	SpawnedTank->SetName(Name);
//
//	if (bSetRenderEnable)
//	{
//		SpawnedTank->EnableRender();
//	}
//
//	TankIndex++;
//
//	return SpawnedTank;
//
//
//}
