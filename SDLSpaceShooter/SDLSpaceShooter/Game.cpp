#include "Game.h"
#include "TextureManager.h"
#include "Timer.h"
#include "GameObject.h"
#include "ECS.h"
#include "Components.h"

GameObject* player;
GameObject* meteor;

Entity::Manager manager;
auto& newPlayer(manager.addEntity());


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
			SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
		cout << "ERROR SDL DID NOT RUN";
	}

	player = new GameObject("Assets/SpaceShip.png", gRenderer, 0, 0);
	meteor = new GameObject("Assets/Meteor.png", gRenderer, 200, 200);

	newPlayer.addComponent<PositionComponent>();
	newPlayer.getComponent<PositionComponent>().setPosition(200, 200);
}

void Game::HandelEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
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
	player->Update();
	meteor->Update();
	manager.update();
	
	std::cout << newPlayer.getComponent<PositionComponent>().x() << "," 
		<< newPlayer.getComponent<PositionComponent>().y() << endl;
}

void Game::Render()
{
	SDL_RenderClear(gRenderer);

	player->Render();
	meteor->Render();

	SDL_RenderPresent(gRenderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	SDL_Quit();
	cout << "Game Cleaned" << endl;
}