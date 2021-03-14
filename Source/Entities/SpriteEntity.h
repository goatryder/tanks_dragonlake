#pragma once

#include "RenderBase.h"

class Sprite;
class Framework;

class SpriteEntity : public RenderBase
{
public:

	SpriteEntity(const char* RelativeResourcePath);
	~SpriteEntity();

	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual void onRender() override;

	inline virtual void CreateSprite();
	inline virtual void DestroySprite();
	
	inline virtual void DrawSprite(VecInt2D Position);

protected:

	std::string ResourceImagePath;
	Sprite* SpriteObj = nullptr;

public:

	static SpriteEntity* SpawnBasicSprite(const char* ResourceImagePath, VecInt2D Position, bool bInitialize = false);
};