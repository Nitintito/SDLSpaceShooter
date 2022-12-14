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
auto& Earth(manager.addEntity());
auto& Background(manager.addEntity());

auto& players(manager.getGroup(Game::groupPlayers));
auto& meteors(manager.getGroup(Game::groupMeteors));
auto& projectiles(manager.getGroup(Game::groupProjectiles));
auto& backGrounds(manager.getGroup(Game::groupbackGrounds));

std::vector<ColliderComponent*> Game::colliders;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title,int width, int height, bool fullScreen)
{
	srand((unsigned)time(NULL));

	int flags = 0;
	if (fullScreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
		if (gRenderer)
		{
			SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		}
		isRunning = true;
	}

	AddTextures();
	CreateBackground();
	CreatePlayer();

	spawnNewWave(waveSize);
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
	
	manager.refresh();
	manager.update();

	if (manager.isGroupEmpty(groupMeteors))
	{
		spawnNewWave(waveSize);
	}


	for (auto& m : meteors)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, m->getComponent<ColliderComponent>().collider))
		{
 			m->destroy();

			cout << "Player HP: " << player.getComponent<HealthComponent>().getHealth() << endl;
			player.getComponent<HealthComponent>().takeDamage(meteorDamage);

			if (player.getComponent<HealthComponent>().getHealth() <= 0)
			{
				gameOver = true;
			}
		}
		else if (Collision::AABB(Earth.getComponent<ColliderComponent>().collider, m->getComponent<ColliderComponent>().collider))
		{
			m->destroy();
			Earth.getComponent<HealthComponent>().takeDamage(meteorDamage);

			cout << "Earth HP: " << Earth.getComponent<HealthComponent>().getHealth() << endl;
			if (Earth.getComponent<HealthComponent>().getHealth() <= 0)
			{
				Earth.getComponent<SpriteComponent>().setTexture("EarthDestroyed");
				gameOver = true;
			}
		}

		for (auto& p : projectiles)
		{
			if (Collision::AABB(m->getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
			{
				m->destroy();
				p->destroy();
				score += meteorScoreValue;
				cout << "Score: " <<  score << endl;
			}
		}
	}
	
}

void Game::Render()
{
	SDL_RenderClear(gRenderer);

	for (auto& b : backGrounds)
	{
		b->draw();
	}
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

void Game::spawnNewWave(int size)
{
	for (int i = 0; i < size; i++)
	{
		assetManager->CreateRandomMeteor(Vector2().Zero(), "Meteor");
	}
	waveSize++;
}


void Game::Clean()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	SDL_Quit();
}

void Game::AddTextures()
{
	assetManager->AddTexture("Player", "Assets/SpaceShip.png");
	assetManager->AddTexture("Meteor", "Assets/Meteor.png");
	assetManager->AddTexture("Projectile", "Assets/Projectile.png");
	assetManager->AddTexture("Earth", "Assets/Earth.png");
	assetManager->AddTexture("Background", "Assets/Background.png");
	assetManager->AddTexture("EarthDestroyed", "Assets/EarthDestroyed.png");
}

void Game::CreateBackground()
{
	Background.addComponent<TransformComponent>(-100, -100, 600, 800, 2);
	Background.addComponent<SpriteComponent>("Background");
	Background.addGroup(groupbackGrounds);

	Earth.addComponent<TransformComponent>(0, 568, 16, 400, 2);
	Earth.addComponent<SpriteComponent>("Earth");
	Earth.addComponent<ColliderComponent>("Earth");
	Earth.addComponent<HealthComponent>(earthHp);
	Earth.addGroup(groupbackGrounds);
}

void Game::CreatePlayer()
{
	player.addComponent<TransformComponent>(400, 530, 2);
	player.addComponent<SpriteComponent>("Player");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("Player");
	player.addComponent<HealthComponent>(playerHp);
	player.addGroup(groupPlayers);
}


