#pragma once

#include <vector>
#include <type_traits>
#include <algorithm>


class TickInterface;

/** This static class will handle onTick for TickInterface instances */
class SystemTick
{
protected:

	static std::vector<TickInterface*> TickQueue;

public:

	static SystemTick& Instance()
	{
		static SystemTick* Instance = new SystemTick();
		return *Instance;
	}

	// @ToDo: move to private, add friend class TickInterface
	/** add tick object to vector queue. called from TickInterface instanses on construct*/
	static void AddTickObj(TickInterface* TickInterfaceInstance)
	{
		TickQueue.push_back(TickInterfaceInstance);
	}

	// @Todo: move to private, add friend class TickInterface
	/* remove tick object from vector queue, called from TickInterface instanses on destroy */
	static void RemoveTickObj(TickInterface* TickInterfaceInstance)
	{
		if (TickInterfaceInstance == TickQueue.back())
		{
			TickQueue.pop_back();
			return;
		}

		std::vector<TickInterface*>::iterator Iter;
		Iter = std::find(TickQueue.begin(), TickQueue.end(), TickInterfaceInstance);
		
		if (Iter != TickQueue.end())
		{
			TickQueue.erase(Iter);
		}
	}

	/* get tick objects vector queue */
	static const std::vector<TickInterface*>& GetTickQueue()
	{
		return TickQueue;
	}

	/** calls onTick for each tick object in vector queue */
	static void Tick(unsigned int DeltaTime);

private:

	SystemTick() {}
};