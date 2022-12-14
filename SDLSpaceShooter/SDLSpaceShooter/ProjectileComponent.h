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
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
		transform->speed = speed;
	}

	void update() override
	{
		distance += travleDistance;

		/*if (distance > range)
		{
			std::cout << "out of range" << std::endl;
			entity->deleteGroup(Game::groupProjectiles);
		}*/
		if (transform->position.y < 0)
		{
			std::cout << "Out of bounds!" << std::endl;
			entity->destroy();
			//entity->destroy();
		}
		//TODO Else if out of bounds
	}

private:

	TransformComponent* transform;

	Vector2 velocity;
	int range = 0;
	int distance = 0;
	int speed = 0;
	int travleDistance = (velocity.x + velocity.y) * speed;
};