#pragma once

#include <vector>
#include <type_traits>

class SpriteEntity;


class SpriteManager
{
public:
	static SpriteManager& Instance()
	{
		static SpriteManager* Instance = new SpriteManager();
		return *Instance;
	}

	/** add sprite to vector queue */
	static void AddSprite(SpriteEntity* Entity);

	/* remove sprite from vector queue and delete */
	static void RemoveSprite(SpriteEntity* Entity);

	/* get SpriteEntity vector queue */
	static const std::vector<SpriteEntity*>& GetSprites();

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
	static void DrawSprites();

protected:
	static std::vector<SpriteEntity*> SpriteEntities;

private:
	SpriteManager() {}
};