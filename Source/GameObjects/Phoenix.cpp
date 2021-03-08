#include "Phoenix.h"
#include "../Helpers/DebugPrint.h"
#include "../Entities/SpriteEntity.h"

Phoenix::Phoenix(SpriteEntity* SpriteObj, VecInt2D Position)
	: SpriteObj(SpriteObj)
{
	this->Position = Position;

	SpriteObj->SetPosition(Position);

	SetSize(SpriteObj->GetSize());

	SetHealth(1);

	SetName("Phoenix");

	EnableCollsion();
}

Phoenix::~Phoenix()
{
}

void Phoenix::onDead()
{
	onDestroy();
}

void Phoenix::onRender()
{
	SpriteObj->onRender();
}

void Phoenix::onDestroy()
{
	RenderBase::onDestroy();

	PRINTF(PrintColor::Red, "delete %s", GetName());
	
	delete this;
}

Phoenix* Phoenix::SpawnPhoenix(VecInt2D Position, Anchor Anchor, const char* ResourcePath, bool bSetRenderEnable)
{
	SpriteEntity* PhoenixSprite = new SpriteEntity(ResourcePath);
	Position -= GetAnchorOffset(PhoenixSprite->GetSize(), Anchor);

	Phoenix* SpawnedPhoenix = new Phoenix(PhoenixSprite, Position);


	if (bSetRenderEnable)
	{
		SpawnedPhoenix->EnableRender();
	}

	return SpawnedPhoenix;
}
