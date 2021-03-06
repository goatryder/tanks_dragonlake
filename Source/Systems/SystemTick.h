#pragma once

#include <vector>
#include <algorithm>


class TickInterface;

/** This static class will handle onTick for TickInterface instances */
class SystemTick
{
protected:

	static std::vector<TickInterface*> TickQueue;

public:

	/** add tick object to TickQueue. called from TickInterface instanses on construct*/
	static void AddTickObj(TickInterface* TickInterfaceInstance)
	{
		TickQueue.push_back(TickInterfaceInstance);
	}

	/* remove tick object from TickQueue, called from TickInterface instanses on destroy */
	static void RemoveTickObj(TickInterface* TickInterfaceInstance)
	{
		std::vector<TickInterface*>::iterator Iter;
		Iter = std::find(TickQueue.begin(), TickQueue.end(), TickInterfaceInstance);
		
		if (Iter != TickQueue.end())
		{
			TickQueue.erase(Iter);
		}
	}

	/** calls onTick for each tick object in TickQueue */
	static void Tick(unsigned int DeltaTime);
};