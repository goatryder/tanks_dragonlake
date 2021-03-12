#pragma once

#include "Booster.h"

class BoosterHP : public Booster
{
public:

	BoosterHP(SpriteEntity* SpriteObj, VecInt2D Position) : Booster(SpriteObj, Position), ExtraLifeVal(1) {}
	~BoosterHP() {}

	int ExtraLifeVal;

	virtual void Activate(LevelStruct* Level, Tank* BoostedTank) override;

public:

	static BoosterHP* SpawnHPBooster(VecInt2D Position);
};