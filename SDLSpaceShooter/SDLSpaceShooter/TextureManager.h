#pragma once

#include "Game.h"

struct TextureManager
{
	static SDL_Texture* LoadTexture(const char* fileName);
	static void DrawTexture(SDL_Texture* texture, SDL_Rect srcPos, SDL_Rect destPos, double angle = 0.0);
};