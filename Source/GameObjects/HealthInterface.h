#pragma once


class HealthInterface
{
public:

	HealthInterface() {}
	~HealthInterface() {}

	int Health = 1;
	bool bIsDead = false;

	virtual void onDead()
	{
		bIsDead = true;
	}

	virtual void onDamage(int Damage)
	{
		int NewHealth = Health - Damage;

		if (NewHealth < 0)
		{
			Health = 0;
		}

		Health = NewHealth;

		if (Health == 0)
		{
			onDead();
		}
	}
};