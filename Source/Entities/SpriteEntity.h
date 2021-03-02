#pragma once

#include "Structs/VecInt2D.h"

class Sprite;
class Framework;

class SpriteEntity
{
public:

	SpriteEntity(const char* ResourceImagePath);
	~SpriteEntity();

	const VecInt2D GetPosition();
	void SetPosition(VecInt2D Val);
	
	bool GetEnable();
	void SetEnable(bool Val);

	const VecInt2D GetSize();

	bool CheckCollision(SpriteEntity* OtherEntity);

	// @ToDo: to private, expose to friend SpriteManager
	virtual void DrawSprite();

protected:

	const char* ResourceImagePath;
	
	Sprite* SpriteObj;
	
	bool bEnabled;
	VecInt2D Size;
	VecInt2D Position;

	inline virtual void CreateSprite();
	inline virtual void DestroySprite();
	
	inline void InitSpriteSize();
};