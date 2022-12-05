#include "Game.h"
#include "TextureManager.h"
#include "Components.h"
#include "Vector2.h"

Manager manager;
auto& player(manager.addEntity());

SDL_Renderer* Game::gRenderer = nullptr;

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

	player.addComponent<TransformComponent>();
	player.addComponent<SpriteComponent>("Assets/SpaceShip.png");


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
	//manager.refresh();
	manager.update();
	player.getComponent<TransformComponent>().position.Add(Vector2(1, 0));
	if (player.getComponent<TransformComponent>().position.x > 100)
	{
		player.getComponent<TransformComponent>().position.Add(Vector2(5, 0));
		player.getComponent<SpriteComponent>().setTexture("Assets/Meteor.png");
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