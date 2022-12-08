#pragma once

#include "Game.h"
#include "ECS.h"
#include "Components.h"
#include "AssetManager.h"

class KeyboardController : public Component
{
private:

public:
	TransformComponent* transform;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{
		if (Game::gEvent.type == SDL_KEYDOWN)
		{
			switch (Game::gEvent.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				break;
			case SDLK_d:
				transform->velocity.x= 1;
				break;
			case SDLK_SPACE:
				std::cout << "request shoot" << endl;
				Game::assetManager->CreateProjectile(Vector2(400, 400), Vector2(1, 0), 30, 5, "Projectile");
				break;
			default:
				break;
			}
		}

		if (Game::gEvent.type == SDL_KEYUP)
		{
			switch (Game::gEvent.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				break;
			default:
				break;
			}
		}
	}
};

