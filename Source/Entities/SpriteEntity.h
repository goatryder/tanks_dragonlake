#pragma once

#include "RenderBase.h"

class Sprite;
class Framework;

class SpriteEntity : public RenderBase
{
public:

	SpriteEntity(const char* ResourceImagePath);
	~SpriteEntity();

	virtual void onRender() override;

protected:

	const char* ResourceImagePath;
	Sprite* SpriteObj;

	inline virtual void CreateSprite();
	inline virtual void DestroySprite();

public:

	static SpriteEntity* SpawnBasicSprite(const char* ResourceImagePath, VecInt2D Position, bool bSetRenderEnable = true);
};