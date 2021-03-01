#pragma once

#include "SpriteEntity.h"

/* SpriteFlipFlop, can be initialized as SpriteEntity and act accordingly
 * but also can have another sprite and act as FlipFlop
 * right now for proper work it's expect Flip Sprite and Flop Sprite has same size
 * @ToDo: handle Flip Flop change on time delay
 */
class SpriteFlipFlop : public SpriteEntity
{
public:

	SpriteFlipFlop(const char* ResourceImagePathFlip);
	SpriteFlipFlop(const char* ResourceImagePathFlip, const char* ResourceImagePathFlop);
	~SpriteFlipFlop();

	/*
	 * If SpriteFlipFlop instance was initialized as SpriteEntity 
	 * it will behave as normal SpriteEntity
	 * this method allow appling flip flop mechanic after initializtion
	 */
	void FlopSpriteInitLazy(const char* ResourceImagePathFlop);

	virtual void DrawSprite() override final;

protected:

	const char* ResourceImagePathSibling = (char*)0;

	Sprite* SpriteObjSibling = nullptr;

	/** if True DrawSprite will draw Inherited SpriteObj else SpriteObjSibling */
	bool bFlipFlop = true;

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
};