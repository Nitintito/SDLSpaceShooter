#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
using namespace std;

class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool fullScreen);

	void HandelEvents();
	void Update();
	void Render();
	void Clean();

	bool Running() { return isRunning; };

	static SDL_Renderer *gRenderer;
	static SDL_Event gEvent;
	static vector<ColliderComponent*> colliders;

private:

	bool isRunning = false;
	SDL_Window *gWindow;

	int frameCounter = 0;
};