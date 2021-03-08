#pragma once

#include "RenderBase.h"

class Sprite;
class Framework;

class SpriteEntity : public RenderBase
{
public:

	SpriteEntity(const char* ResourceImagePath);
	~SpriteEntity();

	virtual void Initialize() override;
	virtual void onRender() override;

	inline virtual void CreateSprite();
	inline virtual void DestroySprite();

protected:

	const char* ResourceImagePath;
	Sprite* SpriteObj = nullptr;

public:

	static SpriteEntity* SpawnBasicSprite(const char* ResourceImagePath, VecInt2D Position, bool bInitialize = false);
};