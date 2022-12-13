#pragma once

#include "ECS.h"
#include "Components.h"
#include "Vector2.h"
#include <iostream>
#include <random>

class MeteorComponent : public Component
{
public:
	MeteorComponent(float scale, int speed, Vector2 velocity) : scale(scale), speed(speed), velocity(velocity)
	{}

	MeteorComponent(bool random) : random(random)
	{}

	~MeteorComponent()
	{}


	void init() override
	{
		if (random)
		{
			float rndVelocityY = RandomFloat(0.1, 1);
			float rndVelocityX = RandomFloat(rndVelocityY/2, -rndVelocityY/2);
			float rndScale = 1 + (rand() % 5);
			int rndSpeed = 1 + (rand() % 5);
			int rndPosX = (rand() % 700);
			int rndPosY = (rand() % 600);

			velocity = Vector2(rndVelocityX, rndVelocityY);
			position = Vector2(rndPosX, -100);
			scale = rndScale;
			speed = rndSpeed;
		}

		transform = &entity->getComponent<TransformComponent>();
		transform->position = position;
		transform->velocity = velocity;
		transform->speed = speed;
		transform->scale = scale;

	}

	float RandomFloat(float Min, float Max)
	{
		return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
	}

private:
	TransformComponent* transform;
	Vector2 position;
	Vector2 velocity;
	float scale = 0;
	int speed = 0;
	bool random;
};