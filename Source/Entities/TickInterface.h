#pragma once

#include "../Systems/SystemTick.h"


class TickInterface
{
public:

	bool bTickEnabled = true;

	virtual void onTick(unsigned int DeltaTime) {}

protected:

	TickInterface()
	{
		SystemTick::AddTickObj(this);
	}

	~TickInterface()
	{
		SystemTick::RemoveTickObj(this);
	}
};