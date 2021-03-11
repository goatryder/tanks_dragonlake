#include "Boom.h"


std::vector<const char*> Boom::BoomSmallPathVec = { BOOM_SMALL_0, BOOM_SMALL_1, BOOM_SMALL_2 };
std::vector<const char*> Boom::BoomBigPathVec = { BOOM_BIG_0, BOOM_BIG_1 };

int Boom::BoomCount = 0;

Boom* Boom::SpawnBoomSmall(VecInt2D Position)
{
	Boom* SpawnedBoom = new Boom(BoomSmallPathVec, BOOM_SMALL_ANIM_TIME);
	
	SpawnedBoom->SetName("boom_small" + std::to_string(BoomCount));

	SpawnedBoom->SetPosition(Position);
	SpawnedBoom->Initialize();

	BoomCount++;

	return SpawnedBoom;
}

Boom* Boom::SpawnBoomBig(VecInt2D Position)
{
	Boom* SpawnedBoom = new Boom(BoomBigPathVec, BOOM_BIG_ANIM_TIME);

	SpawnedBoom->SetName("boom_big" + std::to_string(BoomCount));

	SpawnedBoom->SetPosition(Position);
	SpawnedBoom->Initialize();

	BoomCount++;

	return SpawnedBoom;
}
