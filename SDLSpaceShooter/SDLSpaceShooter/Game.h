#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
using namespace std;

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


private:

	bool isRunning = false;
	SDL_Window *gWindow;
	SDL_Renderer* gRenderer;

	int frameCounter = 0;
};