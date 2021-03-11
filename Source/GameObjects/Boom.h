#pragma once

#include "../Entities/SpriteSequence.h"

class Boom : public SpriteSequence
{
	Boom(std::vector<const char*> BoomPathVec, int AnimTime) : SpriteSequence(BoomPathVec, AnimTime, true) {}
	~Boom() {}

public:
	static std::vector<const char*> BoomSmallPathVec;
	static std::vector<const char*> BoomBigPathVec;

	static int BoomCount;
	static Boom* SpawnBoomSmall(VecInt2D Position);
	static Boom* SpawnBoomBig(VecInt2D Position);
};