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
	double rotation;

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

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, float sc)
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
	Vector2 getPosition()
	{
		return position;
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

	double rotate(double amount)
	{
		rotation += amount;
		return amount;
	}

};