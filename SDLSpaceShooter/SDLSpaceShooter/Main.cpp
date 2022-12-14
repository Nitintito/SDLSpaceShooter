#include "Game.h"

Game *game = nullptr;


int main(int argc, char* args[])
{
	const int fps = 60;
	const int framedelay = 1000 / fps;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->init("GameName", game->windowL, game->windowH, false);

	while (game->Running())
	{

		frameStart = SDL_GetTicks();

		game->HandelEvents();
		game->Update();
		game->Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (framedelay > frameTime)
		{
			SDL_Delay(framedelay - frameTime);
		}
	}

	game->Clean();

	return 0;
}