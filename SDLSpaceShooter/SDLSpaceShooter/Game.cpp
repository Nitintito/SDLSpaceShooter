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
auto& meteor(manager.addEntity());

auto& players(manager.getGeroup(Game::groupPlayers));
auto& meteors(manager.getGeroup(Game::groupMeteors));
auto& projectiles(manager.getGeroup(Game::groupProjectiles));

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
	assetManager->AddTexture("Meteor", "Assets/Meteor.png");
	assetManager->AddTexture("Projectile", "Assets/Projectile.png");

	player.addComponent<TransformComponent>(400, 530, 2);
	player.addComponent<SpriteComponent>("Player");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("Player");
	player.addGroup(groupPlayers);
	
	
	assetManager->CreateMeteor(Vector2(200, 200), Vector2(0.5, 0.8), 1, 1, "Meteor");
	assetManager->CreateMeteor(Vector2(400, 400), Vector2(0.8, 0.1), 1, 0.5, "Meteor");
	assetManager->CreateMeteor(Vector2(100, 100), Vector2(0.5, 1), 1, 2, "Meteor");

	assetManager->CreateProjectile(Vector2(400, 400), Vector2(1, 0), 30, 5, "Projectile");
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
	for (auto m : meteors)
	{
		//m->update();
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, m->getComponent<ColliderComponent>().collider))
		{
			//player.getComponent<TransformComponent>().velocity * -1;
			std::cout << "Meteor hit!" << std::endl;
			//m->destroy();
		}
	}

	for (auto& p : projectiles)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			std::cout << "Projectile hit!" << std::endl;
			//p->destroy();
		}
	}
}

void Game::Render()
{
	SDL_RenderClear(gRenderer);

	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& m : meteors)
	{
		m->draw();
	}
	for (auto& p : projectiles)
	{
		p->draw();
	}

	SDL_RenderPresent(gRenderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	SDL_Quit();
	cout << "Game Cleaned" << endl;
}