#pragma once

#include <vector>
#include <algorithm>

class RenderBase;

/*
 * This static class handles render for instances inherited from RenderBase
 * main method Render() calls onRender() (which call framework method drawSprite()) for each in RenderQueue, so order is matter
 */
class SystemRender
{
protected:

	static std::vector<RenderBase*> RenderQueue;

public:

	/** add RenderBase instance to RenderQueue */
	static void AddRenderObj(RenderBase* RenderObj)
	{
		RenderQueue.push_back(RenderObj);
	}

	/* remove RenderBase instance from RenderQueue */
	static void RemoveRenderObj(RenderBase* RenderObj)
	{
		std::vector<RenderBase*>::iterator Iter;
		Iter = std::find(RenderQueue.begin(), RenderQueue.end(), RenderObj);
		
		if (Iter != RenderQueue.end())
		{
			RenderQueue.erase(Iter);
		}
	}

	/** calls onRender() for each RenderBase in RenderQueue */
	static void Render();
};


