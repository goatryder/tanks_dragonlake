#pragma once

#include "RenderBase.h"

#include "Systems/SpritePrototypeManager.h"

class Sprite;
class Framework;

class SpriteEntity : public RenderBase
{
public:

	SpriteEntity(const char* RelativeResourcePath) : ResourceImagePath(RelativeResourcePath)
	{
	}

	~SpriteEntity() {}

	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual void onRender() override;

	virtual void CreateSprite()
	{
		SpriteObj = SpritePrototypeManager::GetSpritePrototype(ResourceImagePath);
		
		if (SpriteObj != nullptr) InitSizeBySprite(SpriteObj);
	}

	void DrawAtPosition(VecInt2D Position) { if (SpriteObj != nullptr) DrawSprite(SpriteObj, Position); }

protected:

	const char* ResourceImagePath;
	Sprite* SpriteObj = nullptr;

public:

	static SpriteEntity* SpawnBasicSprite(const char* ResourceImagePath, VecInt2D Position, bool bInitialize = false);
};