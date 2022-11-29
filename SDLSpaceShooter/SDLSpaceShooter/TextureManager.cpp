#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* textureName, SDL_Renderer* renderer)
{
	SDL_Surface* tempSurface = IMG_Load(textureName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}
