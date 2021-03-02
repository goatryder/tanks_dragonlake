#pragma once

#include <vector>
#include <type_traits>
#include <algorithm>

#include "../Entities/SpriteEntity.h"

#include "../Helpers/DebugPrint.h"

/*
 * This static class handles sprite instances
 * SpriteQueue is sprites render queue, so order is matter
 */
class SpriteManager
{
protected:

	static std::vector<SpriteEntity*> SpriteQueue;

public:

	static SpriteManager& Instance()
	{
		static SpriteManager* Instance = new SpriteManager();
		return *Instance;
	}

	/** add sprite to vector queue */
	static void AddSprite(SpriteEntity* Entity)
	{
		SpriteQueue.push_back(Entity);
	}

	/* remove sprite from vector queue and delete */
	static void RemoveSprite(SpriteEntity* Entity, bool bDestroy=true)
	{
		if (Entity == SpriteQueue.back())
		{
			SpriteQueue.pop_back();
			if (bDestroy) delete Entity;
			return;
		}

		std::vector<SpriteEntity*>::iterator Iter;
		Iter = std::find(SpriteQueue.begin(), SpriteQueue.end(), Entity);
		
		if (Iter != SpriteQueue.end())
		{
			SpriteQueue.erase(Iter);
			if (bDestroy) delete Entity;
		}
	}

	/* get SpriteEntity vector queue */
	static const std::vector<SpriteEntity*>& GetSprites()
	{
		return SpriteQueue;
	}

	/** create new SpriteEntity instance and add it to vector queue */
	template <class T>
	static T* CreateSprite(const char* path) 
	{
		if (std::is_base_of<SpriteEntity, T>::value)
		{
			T* Entity = new T(path);
			SpriteManager::AddSprite(Entity);
			return Entity;
		}
		else 
		{
			return nullptr;
		}
	}

	/** calls DrawSprite for each SpriteEntity in vector queue */
	static void DrawSprites()
	{
		for (auto& Sprite : SpriteQueue)
			Sprite->DrawSprite();
	}

private:

	SpriteManager() {}
};