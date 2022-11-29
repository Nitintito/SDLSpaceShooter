#include "Game.h"

Game *game = nullptr;


int main(int argc, char* args[])
{
	game = new Game();

	game->init("GameName", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	while (game->running())
	{
		game->HandelEvents();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}