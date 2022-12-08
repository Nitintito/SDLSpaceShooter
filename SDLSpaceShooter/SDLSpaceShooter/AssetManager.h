#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2.h"
#include "ECS.h"

class AssetManager
{
public:
	AssetManager(Manager* manager);
	~AssetManager();

	//Gameobjects
	void CreateProjectile(Vector2 pos, int range, Vector2 velocity, int speed, std::string id);


	//textures
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

private:
	Manager* manager;
	std::map<std::string, SDL_Texture*> texture;


};


