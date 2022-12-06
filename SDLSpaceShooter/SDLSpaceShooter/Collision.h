#pragma once
#include <SDL.h>

class Collision
{
public:
	static bool AABB(const SDL_Rect& rectA, SDL_Rect& rectB); // Axis alignd bounding box
};