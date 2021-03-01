#pragma once

#include "Structs/VecInt2D.h"

class Sprite;
class Framework;

class SpriteEntity
{
public:

	SpriteEntity(const char* path);
	~SpriteEntity();

	const VecInt2D GetPosition();
	void SetPosition(VecInt2D Val);
	
	bool GetEnable();
	void SetEnable(bool Val);

	const VecInt2D GetSize();

	bool CheckCollision(SpriteEntity* OtherEntity);

	// @ToDo: to friend sprite render
	void DrawSprite();

protected:
	const char* ResourceImagePath;
	
	Sprite* SpriteObj;
	
	bool bEnabled;
	VecInt2D Size;
	VecInt2D Position;

	inline void CreateSprite();
	inline void DestroySprite();
	inline void InitSpriteSize();
	
};