#pragma once

#include <vector>
#include <type_traits>
#include <algorithm>

#include "../Entities/RenderInterface.h"
#include "../Entities/SpriteEntity.h"
#include "../Helpers/DebugPrint.h"

/*
 * This static class handles instances inherited from RenderInterface
 * main method Render() calls Render() (which call framework method drawSprite) for each in RenderQueue, so order is matter
 */
class SystemRender
{
protected:

	static std::vector<RenderInterface*> RenderQueue;

public:

	static SystemRender& Instance()
	{
		static SystemRender* Instance = new SystemRender();
		return *Instance;
	}

	/** add derrived from RenderInterface instance to vector queue */
	static void AddRenderObj(RenderInterface* RenderObj)
	{
		RenderQueue.push_back(RenderObj);
	}

	/* remove derrived from RenderInterface instance from vector queue and destroy */
	static void RemoveRenderObj(RenderInterface* RenderObj, bool bDestroy=true)
	{
		if (RenderObj == RenderQueue.back())
		{
			RenderQueue.pop_back();
			if (bDestroy) delete RenderObj;
			return;
		}

		std::vector<RenderInterface*>::iterator Iter;
		Iter = std::find(RenderQueue.begin(), RenderQueue.end(), RenderObj);
		
		if (Iter != RenderQueue.end())
		{
			RenderQueue.erase(Iter);
			if (bDestroy) delete RenderObj;
		}
	}

	/* get derrived from RenderInterface instance vector queue */
	static const std::vector<RenderInterface*>& GetRenderQueue()
	{
		return RenderQueue;
	}

	/** create derrived from SpriteEntity instance and add it to vector queue */
	template <class T>
	static T* CreateSprite(const char* path, bool bAddToQueue=true) 
	{
		if (std::is_base_of<SpriteEntity, T>::value)
		{
			T* Entity = new T(path);
			if (bAddToQueue) SystemRender::AddRenderObj(Entity);
			return Entity;
		}
		else 
		{
			return nullptr;
		}
	}

	/** calls onRender() for each RenderInterface in vector queue */
	static void Render()
	{
		for (auto& RenderInstance : RenderQueue)
			RenderInstance->onRender();
	}

private:

	SystemRender() {}
};