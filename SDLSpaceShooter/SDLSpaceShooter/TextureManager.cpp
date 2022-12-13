#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::gRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

void TextureManager::DrawTexture(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, double angle)
{
	SDL_RenderCopyEx(Game::gRenderer, texture, &src, &dest, angle, NULL, SDL_FLIP_NONE);
}
