#pragma once
#include "Components.h"
#include "Vector2.h"

struct TransformComponent : public Component
{

	Vector2 position;

	TransformComponent()
	{
		position.x = 0.0f;
		position.y = 0.0f;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	void update() override
	{
		
	}

};