#pragma once

#include <vector>

#include "SpriteEntity.h"
#include "TickInterface.h"


class SpriteSequence : public SpriteEntity, public TickInterface
{
public:

	SpriteSequence(std::vector<const char*> ResourceImageRelPathVec, unsigned int AnimTime, bool bDestroyOnFirstLoopFinish = false);
	~SpriteSequence();

	virtual void Initialize() override final;
	virtual void Destroy() override final;
	virtual void onRender() override final;

	inline virtual void CreateSprite() override final;
	inline virtual void DestroySprite() override final;
	
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
