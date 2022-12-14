#pragma once

#include "SDL.h"
#include "Components.h"

class HealthComponent : public Component
{
private:
	int health = 5;

public:
	HealthComponent()
	{}
	HealthComponent(int startingHealt) : health(startingHealt)
	{}
	~HealthComponent()
	{}

	void setHealth(int amount) { health = amount; }
	void takeDamage(int amount) { health -= amount; }
	void healDamage(int amount) { health += amount; }

	int getHealth() { return health; }
};