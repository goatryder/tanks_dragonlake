#include "SystemTick.h"

#include "../Entities/TickInterface.h"

// Initialize TickQueue
std::list<TickInterface*> SystemTick::TickQueue = {};

void SystemTick::Tick(unsigned int DeltaTime)
{
	for (auto& TickInterfaceInstance : TickQueue)
	{
		TickInterfaceInstance->onTick(DeltaTime);
	}
}

// check if multiple inheritence call renderBase Destroy
void SystemTick::ClearTickQueue(bool bDestroy)
{
	if (bDestroy)
	{
		for (auto& TickInterfaceInstance : TickQueue)
		{
			TickInterfaceInstance->Destroy();
		}
	}

	TickQueue.clear();
}
