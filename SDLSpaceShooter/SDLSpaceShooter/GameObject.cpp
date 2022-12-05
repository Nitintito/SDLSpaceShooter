#include "GameObject.h"
#include "TextureManager.h"



GameObject::GameObject(const char* textureSheet, int x, int y)
{
	objectTexture = TextureManager::LoadTexture(textureSheet);

	xPos = x;
	yPos = y;
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	yPos++;
	xPos++;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xPos;
	destRect.y = yPos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.w * 2;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::gRenderer, objectTexture, &srcRect, &destRect);
}
