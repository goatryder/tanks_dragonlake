#include "SpritePrototypeManager.h"

#include "GlobalConstants.h"

#include "Framework.h"

#include "Helpers/DebugPrint.h"

std::map<const char*, Sprite*> SpritePrototypeManager::SpritePrototypes = {};

void SpritePrototypeManager::CreateSpritePrototype(const char* RelResourcePath, bool bInitialize)
{
	Sprite* SpriteObj = nullptr;

	if (bInitialize)
	{
		SpriteObj = createSprite(GetResourcePath(RelResourcePath).c_str());
	}

	SpritePrototypes.insert(std::pair<const char*, Sprite*>(RelResourcePath, SpriteObj));
}

void SpritePrototypeManager::DestroySpritePrototype(const char* RelResourcePath)
{
	std::map<const char*, Sprite*>::iterator Iter;

	Iter = SpritePrototypes.find(RelResourcePath);
	
	if (Iter != SpritePrototypes.end())
	{
		SpritePrototypes.erase(Iter);
	
		destroySprite((*Iter).second);
	}
}

Sprite* SpritePrototypeManager::GetSpritePrototype(const char* RelResourcePath)
{
	std::map<const char*, Sprite*>::iterator Iter;

	Iter = SpritePrototypes.find(RelResourcePath);

	if (Iter == SpritePrototypes.end())
	{
		return nullptr;
	}
	else
	{
		return (*Iter).second;
	}
}

void SpritePrototypeManager::Initialize()
{
	for (auto& SpritePair : SpritePrototypes)
	{
		Sprite*& SpriteObj = SpritePair.second;

		if (SpriteObj == nullptr)
		{
			std::string ResourcePath = GetResourcePath(SpritePair.first);
			SpriteObj = createSprite(ResourcePath.c_str());

			PRINTF(PrintColor::Blue, "[SpritePrototypeManager] Sprite prototype created: %s", SpritePair.first);
		}
	}
}

void SpritePrototypeManager::Finalize()
{
	for (auto& SpritePair : SpritePrototypes)
	{
		Sprite*& SpriteObj = SpritePair.second;

		if (SpriteObj != nullptr)
		{
			destroySprite(SpriteObj);
		}
	}

	SpritePrototypes.clear();
}
