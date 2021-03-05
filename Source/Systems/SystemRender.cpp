#include "SystemRender.h"

#include <type_traits>

#include "../Entities/RenderBase.h"

// Initialize RenderQueue list
std::vector<RenderBase*> SystemRender::RenderQueue = {};

void SystemRender::Render()
{
	for (auto& RenderInstance : RenderQueue)
		if (RenderInstance->IsEnabled()) RenderInstance->onRender();
}