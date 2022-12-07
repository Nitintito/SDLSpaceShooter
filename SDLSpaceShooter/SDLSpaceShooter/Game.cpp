#include "Game.h"
#include "TextureManager.h"
#include "Components.h"
#include "Vector2.h"
#include "Collision.h"
#include "AssetManager.h"

Manager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);

SDL_Renderer* Game::gRenderer = nullptr;
SDL_Event Game::gEvent;

auto& player(manager.addEntity());
auto& projectile(manager.addEntity());
auto& wall(manager.addEntity());

std::vector<ColliderComponent*> Game::colliders;

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

	assetManager->AddTexture("Player", "Assets/SpaceShip.png");
	assetManager->AddTexture("Projectile", "Assets/Projectile.png");
	assetManager->AddTexture("Meteor", "Assets/Meteor.png");



	player.addComponent<TransformComponent>(400, 530, 2);
	player.addComponent<SpriteComponent>("Player");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("Player");

	
	wall.addComponent<TransformComponent>(400, 400, 2.0f);
	wall.addComponent<SpriteComponent>("Meteor");
	wall.addComponent<ColliderComponent>("Meteor");

	//assetManager->CreateProjectile(Vector2(700, 700), 200, 2, "Projectile");
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
	manager.update();
	for (auto collider : colliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *collider);
		//{
			//player.getComponent<TransformComponent>().velocity * -1;
			//std::cout << "Wall hit!" << std::endl;
		//}
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