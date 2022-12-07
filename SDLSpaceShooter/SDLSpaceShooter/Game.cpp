#include "Game.h"
#include "TextureManager.h"
#include "Components.h"
#include "Vector2.h"
#include "Collision.h"

Manager manager;

SDL_Renderer* Game::gRenderer = nullptr;
SDL_Event Game::gEvent;

auto& player(manager.addEntity());
auto& projectile(manager.addEntity());
auto& wall(manager.addEntity());



Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullScreen)
{
	int flags = 0;
	if (fullScreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "SDL Initialised!" << endl;
		gWindow = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (gWindow != NULL)
		{
			cout << "Window created!" << endl;
		}

		gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
		if (gRenderer != NULL)
		{
			cout << "Renderer Created" << endl;
			SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
		cout << "ERROR SDL DID NOT RUN";
	}

	player.addComponent<TransformComponent>(400, 530, 2);
	player.addComponent<SpriteComponent>("Assets/SpaceShip.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("Player");

	projectile.addComponent<TransformComponent>(400, 400, 0.3f).velocity = Vector2(0, -2);
	projectile.addComponent<SpriteComponent>("Assets/Projectile.png");
	projectile.addComponent<ColliderComponent>("Projectile");

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("Assets/Meteor.png");
	wall.addComponent<ColliderComponent>("Wall");
}

void Game::HandelEvents()
{
	SDL_PollEvent(&gEvent);

	switch (gEvent.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}

}

void Game::Update()
{
	//manager.refresh();
	manager.update();

	if (Collision::AABB(player.getComponent<ColliderComponent>().collider,
		wall.getComponent<ColliderComponent>().collider))
	{
		player.getComponent<TransformComponent>().velocity * -1;
		//player.destroy();

		std::cout << "Wall hit!" << std::endl;
	}
}

void Game::Render()
{
	SDL_RenderClear(gRenderer);

	manager.draw();

	SDL_RenderPresent(gRenderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	SDL_Quit();
	cout << "Game Cleaned" << endl;
}