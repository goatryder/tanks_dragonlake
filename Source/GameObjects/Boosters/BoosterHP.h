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

	/** Only player on collide can activate this booster */
	static BoosterHP* SpawnPlayerHPBooster(LevelStruct* Level, VecInt2D Position);
};