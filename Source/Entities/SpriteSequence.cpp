#include "SpriteSequence.h"


SpriteSequence::SpriteSequence(std::vector<const char*> ResourceImagePathVec, unsigned int AnimTime, bool bDestroyOnFinish)
	: SpriteEntity(ResourceImagePathVec[0]), ResourceImagePathVec(ResourceImagePathVec), AnimTime(AnimTime), 
	bDestroyOnFirstLoopFinish(bDestroyOnFinish)
{
	AnimTimeAccomulated = 0;
	CurrentSpriteObjIndex = 0;
	SpriteObjVecSize = ResourceImagePathVec.size();
	
	bFirstLoopFinish = false;

	SpriteObjVec = {};
}

SpriteSequence::~SpriteSequence()
{
}

void SpriteSequence::Initialize()
{
	SpriteEntity::Initialize();
	EnableTick();
}

void SpriteSequence::Destroy()
{
	DisableTick();
	SpriteEntity::Destroy();
}

void SpriteSequence::onRender()
{
	SpriteEntity::onRender();
}

inline void SpriteSequence::CreateSprite()
{
	for (auto& Path : ResourceImagePathVec)
	{
		Sprite* SpriteObj = createSprite(Path);
		SpriteObjVec.push_back(SpriteObj);
	}

	this->SpriteObj = SpriteObjVec[0];
	InitSizeBySprite(SpriteObj);
}

inline void SpriteSequence::DestroySprite()
{
	for (auto& Sprite : SpriteObjVec)
	{
		destroySprite(Sprite);
	}
}

void SpriteSequence::onTick(unsigned int DeltaTime)
{
	AnimTimeAccomulated += DeltaTime;

	if (AnimTimeAccomulated >= AnimTime)
	{
		AnimTimeAccomulated = 0;

		if (bDestroyOnFirstLoopFinish && bFirstLoopFinish)
		{
			Destroy();
			return;
		}
		
		int NewSpriteIndex = (CurrentSpriteObjIndex + 1) % SpriteObjVecSize;

		if (NewSpriteIndex + 1 == SpriteObjVecSize)
		{
			bFirstLoopFinish = true;
		}

		CurrentSpriteObjIndex = NewSpriteIndex;

		SpriteObj = SpriteObjVec[NewSpriteIndex];
	}
}

SpriteSequence* SpriteSequence::SpawnSpriteSequence(std::vector<const char*> ResourceImagePathVec, VecInt2D Position, unsigned int AnimTime, bool bInitialize)
{
	SpriteSequence* SpawnedSprite = new SpriteSequence(ResourceImagePathVec, AnimTime);
	SpawnedSprite->SetPosition(Position);

	if (bInitialize)
	{
		SpawnedSprite->Initialize();
	}

	return SpawnedSprite;
}
