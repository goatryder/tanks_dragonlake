#pragma once

#include "../Entities/RenderBase.h"
#include "../Entities/TickInterface.h"

class SpriteEntity;

class BasicUIElement : public RenderBase, public TickInterface
{
public:

	BasicUIElement() {}
	BasicUIElement(SpriteEntity* SpriteObj) : SpriteObj(SpriteObj) {}
	~BasicUIElement() {}

	bool bEnabled = false;

	virtual void onRender() override;
	virtual void Destroy() override;
	virtual void Initialize() override;

	void Enable() { bEnabled = true; }
	void Disable() { bEnabled = false; }

protected:

	SpriteEntity* SpriteObj = nullptr;

public:

	static BasicUIElement* CreateBasicUIElement(const char* ResourcePath, VecInt2D Position);

};