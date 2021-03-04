#pragma once


class HealthInterface
{
public:

	HealthInterface() {}
	~HealthInterface() {}

	int GetHealth() const 
	{ 
		return Health; 
	}
	
	void SetHealth(int NewHealth)
	{
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

	bool IsDead() const { return bIsDead; }

	virtual void onDead()
	{
		bIsDead = true;
	}

	virtual void onDamage(int Damage)
	{
		SetHealth(Health - Damage);
	}

private:
	int Health = 1;
	bool bIsDead = false;

};