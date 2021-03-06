#pragma once

#include "SpriteEntity.h"
#include "TickInterface.h"

/* SpriteFlipFlop, can be initialized as SpriteEntity and act accordingly
 * but also can have another sprite and act as FlipFlop
 * right now for proper work it's expect Flip Sprite and Flop Sprite has same size
 */
class SpriteFlipFlop : public SpriteEntity, public TickInterface
{
public:

	SpriteFlipFlop(const char* ResourceImagePathFlip);
	SpriteFlipFlop(const char* ResourceImagePathFlip, const char* ResourceImagePathFlop, unsigned int FlipFlopTimeMs=0);
	~SpriteFlipFlop();

	/*
	 * If SpriteFlipFlop instance was initialized as SpriteEntity 
	 * it will behave as normal SpriteEntity
	 * this method allow appling flip flop mechanic after initializtion
	 */
	void FlopSpriteInitLazy(const char* ResourceImagePathFlop, unsigned int FlipFlopTimeMs=0);

	virtual void onRender() override final;
	virtual void onDestroy() override final;

protected:

	const char* ResourceImagePathSibling = (char*)0;
	Sprite* SpriteObjSibling = nullptr;

	/** if True DrawSprite will draw Inherited SpriteObj else SpriteObjSibling */
	bool bFlipFlop = true;

	/** Control auto flipFlop on tick */
	bool bAutoFlipFlopEnabled = true;

	/** on tick sprite change, in ms, if 0 - disable */
	unsigned int FlipFlopTime = 0;
	unsigned int FlipFlopTimeAccomulated = 0;

	/*
	 * in parent constructor will be called parent implementation explicitly
	 * so this one will be creation for second Sprite (not best architecture, but ok for now)
	 */
	inline virtual void CreateSprite() override final;

	/*
     * in parent destructor will be called parent implementation explicitly
     * so this one will be destruction for second Sprite (not best architecture, but ok for now)
     */
	inline virtual void DestroySprite() override final;

public:
	
	void SetFlipFlopTime(unsigned int TimeInMs)	{ FlipFlopTime = TimeInMs; }

	unsigned int GetFlipFlopTime() const { return FlipFlopTime; }

	/** manual controlled flip flop */
	void SetFlipFlop(bool bFlipFlop) { this->bFlipFlop = bFlipFlop; }

	bool GetFlipFlop() const { return bFlipFlop; }

	void SetAutoFlipFlopEnable(bool bEnable) { bAutoFlipFlopEnabled = bEnable; }

	bool IsAutoFlipFlopEnabled() const { return bAutoFlipFlopEnabled; }

	virtual void onTick(unsigned int DeltaTime) override;
};