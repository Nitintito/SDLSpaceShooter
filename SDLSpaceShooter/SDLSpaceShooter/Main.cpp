#include "Game.h"

Game *game = nullptr;


int main(int argc, char* args[])
{
	const int fps = 60;
	const int framedelay = 1000 / fps;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->init("GameName", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	while (game->running())
	{

		frameStart = SDL_GetTicks();

		game->HandelEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (framedelay > frameTime)
		{
			SDL_Delay(framedelay - frameTime);
		}
	}

	game->clean();

	return 0;
}