#include "SystemRender.h"

#include "../Entities/RenderBase.h"

// Initialize RenderQueue list
std::list<RenderBase*> SystemRender::RenderQueue = {};

void SystemRender::Render()
{
	std::list<RenderBase*>::iterator Iter;

	for (Iter = RenderQueue.begin(); Iter != RenderQueue.end(); Iter++)
	{
		RenderBase* RenderInstance = (*Iter);

		if (RenderInstance != nullptr)
		{
			RenderInstance->onRender();
		}
	}

	/*for (auto& RenderInstance : RenderQueue)
	{
		if (RenderInstance != nullptr)
		{
			RenderInstance->onRender();
		}
	}*/
}

void SystemRender::ClearRenderQueue(bool bDestroy)
{
	if (bDestroy)
	{
		for (auto& RenderInstance : RenderQueue)
		{
			if (RenderInstance != nullptr)
			{
				RenderInstance->Destroy();
			}
		}
	}

	RenderQueue.clear();
}
