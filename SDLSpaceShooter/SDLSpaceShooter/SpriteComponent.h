#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "AssetManager.h"

class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;
	double angle;
	double rotationAmount = 0;

public:

	SpriteComponent() = default;
	SpriteComponent(std::string id)
	{
		setTexture(id);
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void setTexture(std::string id)
	{
		texture = Game::assetManager->GetTexture(id);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
		//destRect.w = transform->width * transform->scale;
		//destRect.h = transform->height * transform->scale;
	}

	void update() override
	{
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;

		//angle = transform->rotate(rotationAmount);
	}

	void draw() override
	{
		TextureManager::DrawTexture(texture, srcRect, destRect, angle);
	}
};