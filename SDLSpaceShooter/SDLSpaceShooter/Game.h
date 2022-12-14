#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
using namespace std;

class AssetManager;
class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullScreen);

	void HandelEvents();
	void Update();
	void Render();
	void Clean();

	void AddTextures();
	void CreateBackground();
	void CreatePlayer();
	void spawnNewWave(int size);

	const int windowL = 800, windowH = 600;

	int playerSpeed = 5;
	int playerHp = 5;
	int earthHp = 10;
	int meteorDamage = 1;

	int waveSize = 1;
	int score = 0;
	int meteorScoreValue = 100;

	static bool isRunning;
	bool gameOver = false;



	
	bool Running() { return isRunning; };

	static SDL_Renderer *gRenderer;
	static SDL_Event gEvent;
	static vector<ColliderComponent*> colliders;
	static AssetManager* assetManager;

	enum  groupLabls : std::size_t
	{
		groupPlayers,
		groupMeteors,
		groupProjectiles,
		groupbackGrounds
	};

private:

	SDL_Window *gWindow;
	int frameCounter = 0;
};