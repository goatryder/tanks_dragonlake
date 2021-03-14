#pragma once

#include <map>

class Sprite;

/*
 * This static class store Sprite objects to avoid multiple creation of the same sprite
 */
class SpritePrototypeManager
{
public:

	static std::map<const char*, Sprite*> SpritePrototypes;

public:

	static SpritePrototypeManager& Instance()
	{
		static SpritePrototypeManager* Instance = new SpritePrototypeManager();
		return *Instance;
	}

	static void CreateSpritePrototype(const char* RelResourcePath, bool Initialize = false);
	static void DestroySpritePrototype(const char* RelResourcePath);

	static Sprite* GetSpritePrototype(const char* RelResourcePath);

	static void Initialize();
	static void Finalize();

public:

	SpritePrototypeManager() {}
	~SpritePrototypeManager() {}

};