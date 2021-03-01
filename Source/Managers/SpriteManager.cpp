#include "SpriteManager.h"

#include "../Entities/SpriteEntity.h"

#include <algorithm>

// Initialize SpriteEntities list
std::vector<SpriteEntity*> SpriteManager::SpriteEntities = {};

void SpriteManager::AddSprite(SpriteEntity* Entity)
{
	SpriteEntities.push_back(Entity);
}

void SpriteManager::RemoveSprite(SpriteEntity* Entity)
{
	std::vector<SpriteEntity*>::iterator Iter;

	Iter = std::find(SpriteEntities.begin(), SpriteEntities.end(), Entity);
	SpriteEntities.erase(Iter);

	delete Entity;
}

const std::vector<SpriteEntity*>& SpriteManager::GetSprites()
{
	return SpriteEntities;
}

SpriteEntity* SpriteManager::CreateSprite(const char* path)
{
	SpriteEntity* Entity = new SpriteEntity(path);
	SpriteManager::AddSprite(Entity);

	return Entity;
}

void SpriteManager::DrawSprites()
{
	for (auto& Sprite : SpriteEntities)
	{
		Sprite->DrawSprite();
	}
}
