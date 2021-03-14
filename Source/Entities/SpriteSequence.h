#pragma once

#include <vector>

#include "SpriteEntity.h"
#include "TickInterface.h"


class SpriteSequence : public SpriteEntity, public TickInterface
{
public:

	SpriteSequence::SpriteSequence(std::vector<const char*> ResourceImageRelPathVec, unsigned int AnimTime, bool bDestroyOnFinish = false)
		: SpriteEntity(ResourceImageRelPathVec[0]),
		ResourceImageRelPathVec(ResourceImageRelPathVec),
		AnimTime(AnimTime), bDestroyOnFirstLoopFinish(bDestroyOnFinish)
	{
		AnimTimeAccomulated = 0;
		CurrentSpriteObjIndex = 0;
		SpriteObjVecSize = ResourceImageRelPathVec.size();

		bFirstLoopFinish = false;

		SpriteObjVec = {};
	}

	~SpriteSequence() {}

	virtual void CreateSprite() override final
	{
		for (auto& Path : ResourceImageRelPathVec)
		{
			Sprite* SpriteObj = SpritePrototypeManager::GetSpritePrototype(Path);
			SpriteObjVec.push_back(SpriteObj);
		}
	}

	virtual void Initialize() override final;
	virtual void Destroy() override final;

	virtual void onTick(unsigned int DeltaTime) override final;

protected:

	bool bDestroyOnFirstLoopFinish;
	bool bFirstLoopFinish;

	unsigned int AnimTime;
	unsigned int AnimTimeAccomulated;
	
	int CurrentSpriteObjIndex;
	int SpriteObjVecSize;

	std::vector<const char*> ResourceImageRelPathVec;
	std::vector<Sprite*> SpriteObjVec;

public:

	static SpriteSequence* SpawnSpriteSequence(std::vector<const char*> ResourceImageRelPathVec,
		VecInt2D Position, unsigned int AnimTime, bool bInitialize = false);
};
