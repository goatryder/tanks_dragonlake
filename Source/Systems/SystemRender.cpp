#include "SystemRender.h"

#include "../Entities/RenderBase.h"

// Initialize RenderQueue list
std::list<RenderBase*> SystemRender::RenderQueue = {};

void SystemRender::Render()
{
	for (auto& RenderInstance : RenderQueue)
		RenderInstance->onRender();
}

void SystemRender::ClearRenderQueue(bool bDestroy)
{
	if (bDestroy)
	{
		for (auto& RenderInstance : RenderQueue)
		{
			RenderInstance->Destroy();
		}
	}

	RenderQueue.clear();
}
