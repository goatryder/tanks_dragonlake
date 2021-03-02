#pragma once

#include "RenderInterface.h"

class Sprite;
class Framework;

class SpriteEntity : public RenderInterface
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
};