#pragma once

#include <list>
#include <algorithm>


class TickInterface;

/** This static class will handle onTick for TickInterface instances */
class SystemTick
{
public:

	static std::list<TickInterface*> TickQueue;

public:

	static SystemTick& Instance()
	{
		static SystemTick* Instance = new SystemTick();
		return *Instance;
	}

	/** add tick object to TickQueue. called from TickInterface instanses on construct*/
	static void AddTickObj(TickInterface* TickInterfaceInstance)
	{
		TickQueue.push_back(TickInterfaceInstance);
	}

	/* remove tick object from TickQueue, called from TickInterface instanses on destroy */
	static void RemoveTickObj(TickInterface* TickInterfaceInstance)
	{
		std::list<TickInterface*>::iterator Iter;
		Iter = std::find(TickQueue.begin(), TickQueue.end(), TickInterfaceInstance);
		
		if (Iter != TickQueue.end())
		{
			TickQueue.erase(Iter);
		}
	}

	/** clear TickQueue, can be used on level change */
	static void ClearTickQueue(bool bDestroy = false);

	/** calls onTick for each tick object in TickQueue */
	static void Tick(unsigned int DeltaTime);

public:

	SystemTick() {}
	~SystemTick() {}
};