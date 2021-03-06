#include "SystemTick.h"

#include "../Entities/TickInterface.h"

// Initialize TickQueue
std::vector<TickInterface*> SystemTick::TickQueue = {};

void SystemTick::Tick(unsigned int DeltaTime)
{
	for (auto& TickInterfaceInstance : TickQueue)
	{
		TickInterfaceInstance->onTick(DeltaTime);
	}
}
