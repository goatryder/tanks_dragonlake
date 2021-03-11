#pragma once

enum class Direction;

class HealthInterface
{
public:

	HealthInterface() {}
	~HealthInterface() {}

	/** Get Current Health */
	int GetHealth() const 
	{ 
		return Health; 
	}

	/** Get Base Full Health */
	int GetBaseHealth() const
	{
		return BaseHealth;
	}
	
	/** Set Health, flag bResetBaseHealth allow to reset base full HP */
	void SetHealth(int NewHealth, bool bResetBaseHealth = false)
	{

		if (NewHealth <= 0)
		{
			Health = 0;
			
			bIsDead = true;

			onDead();
		}
		else
		{
			Health = NewHealth;

			if (bResetBaseHealth)
			{
				BaseHealth = NewHealth;
				
				bIsDead = false;
			}
		}
	}

	bool IsDead() const { return bIsDead; }

	virtual void onDead() {}

	virtual void onDamage(int Damage, Direction From)
	{
		SetHealth(Health - Damage);
	}

private:

	int Health = 1;
	int BaseHealth = 1;
	bool bIsDead = false;

};