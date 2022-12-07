#pragma once

#include "ECS.h"
#include "Components.h"

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(int range, int speed) : range(range), speed(speed)
	{}

	~ProjectileComponent()
	{}

	void init() override
	{
		transfom = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{
		distance += speed;

		if (distance > range)
		{
			entity->destroy();
		}
		//TODO Else if out of bounds
	}

private:

	TransformComponent* transfom;

	int range = 0;
	int speed = 0;
	int distance = 0;
};