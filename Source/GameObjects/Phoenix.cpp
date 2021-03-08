#include "Phoenix.h"
#include "../Helpers/DebugPrint.h"
#include "../Entities/SpriteEntity.h"

Phoenix::Phoenix(SpriteEntity* SpriteObj, VecInt2D Position)
	: SpriteObj(SpriteObj)
{
	this->Position = Position;
	SpriteObj->SetPosition(Position);

	SetHealth(1);
	SetName("Phoenix");
}

Phoenix::~Phoenix()
{
}

void Phoenix::onDead()
{
	Destroy();
}

void Phoenix::onRender()
{
	SpriteObj->onRender();
}

void Phoenix::Destroy()
{
	RenderBase::Destroy();

	PRINTF(PrintColor::Red, "delete %s", GetName());
	
	delete this;
}

void Phoenix::Initialize()
{
	SpriteInit();
	EnableRender();
	EnableCollsion();
}

void Phoenix::SpriteInit()
{
	SpriteObj->CreateSprite();
	SetSize(SpriteObj->GetSize());
}

Phoenix* Phoenix::SpawnPhoenix(VecInt2D Position, Anchor Anchor, const char* ResourcePath, bool bInitialize)
{
	// hack to get anchor offset
	VecInt2D PhoenixSpriteSize(GAME_CHUNK_W, GAME_CHUNK_H);

	SpriteEntity* PhoenixSprite = new SpriteEntity(ResourcePath);
	Position -= GetAnchorOffset(PhoenixSpriteSize, Anchor);

	Phoenix* SpawnedPhoenix = new Phoenix(PhoenixSprite, Position);


	if (bInitialize)
	{
		SpawnedPhoenix->Initialize();
	}

	return SpawnedPhoenix;
}
