#pragma once

#include "../Systems/SystemTick.h"


class TickInterface
{
public:

	TickInterface() {}
	~TickInterface() {}

	void EnableTick()
	{
		bTickEnabled = true;
		SystemTick::AddTickObj(this);
	}

	void DisableTick()
	{
		bTickEnabled = false;
		SystemTick::RemoveTickObj(this);
	}

	bool bIsTickEnabled()
	{
		return bTickEnabled;
	}

	virtual void onTick(unsigned int DeltaTime) {}

protected:

	bool bTickEnabled = false;
};