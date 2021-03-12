#include "Booster.h"
#pragma once

#include "../../Entities/SpriteEntity.h"
#include "../LevelStruct.h"


Booster::Booster(SpriteEntity* SpriteObj, VecInt2D Position)
	: SpriteObj(SpriteObj)
{
	this->Position = Position;
	SpriteObj->SetPosition(Position);
}

void Booster::onRender()
{
	SpriteObj->onRender();
}

void Booster::Destroy()
{
	SpriteObj->Destroy();

	RenderBase::Destroy();

	delete this;
}

void Booster::Initialize()
{
	SpriteInit();
	EnableRender();
	EnableCollsion();
}

void Booster::onCollide(RenderBase* Other, CollisionFilter Filter)
{
	LevelStruct* LevelOwner = GetLevel();

	if (LevelOwner != nullptr)
	{
		if (LevelOwner->PlayerTank == Other) // check if player tank
		{ 
			Activate(LevelOwner, static_cast<Tank*>(Other));
			Destroy();
		}
	}
}

void Booster::SpriteInit()
{
	SpriteObj->CreateSprite();
	SetSize(SpriteObj->GetSize());
}

template<class T>
inline T* Booster::SpawnBooster(const char* SpriteResourcePath, VecInt2D Position)
{
	if (std::is_base_of<Booster, T>::value)
	{
		SpriteEntity* BoosterSprite = new SpriteEntity(SpriteResourcePath);

		T* SpawnedBooster = new T(BoosterSprite, Position);

		SpawnedBooster->Initialize();

		return SpawnedBooster;
	}
	else
	{
		return nullptr;
	}
}