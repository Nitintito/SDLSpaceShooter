#pragma once

#include "ECS.h"
#include "Components.h"
#include "Vector2.h"

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(int range, int speed, Vector2 velocity) : range(range), speed(speed), velocity(velocity)
	{}

	~ProjectileComponent()
	{}

	void init() override
	{
		transfom = &entity->getComponent<TransformComponent>();
		transfom->velocity = velocity;
		std::cout << transfom->position << std::endl;
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
	Vector2 velocity;
};