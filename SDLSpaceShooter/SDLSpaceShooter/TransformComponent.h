#pragma once

#include "Components.h"
#include "Vector2.h"

struct TransformComponent : public Component
{
	Vector2 position;
	Vector2 velocity;
	
	int height = 32;
	int width = 32;
	float scale = 1;

	int speed = 3;

	TransformComponent()
	{
		position.Zero();
	}

	TransformComponent(float sc)
	{
		position.Zero();
		scale = sc;
	}

	TransformComponent(int x, int y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(int x, int y, float sc)
	{
		position.x = x;
		position.y = y;
		scale = sc;
	}

	TransformComponent(float x, float y, int h, int w, float sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override
	{
		velocity.Zero();
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

};