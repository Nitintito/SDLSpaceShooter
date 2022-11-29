#include <SDL.h>
#include <iostream>
using namespace std;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, float xPos, float yPos, int width, int height, bool fullScreen);

	void HandelEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; };


private:

	bool isRunning;
	SDL_Window *gWindow;
	SDL_Renderer* gRenderer;

	int frameCounter = 0;

};