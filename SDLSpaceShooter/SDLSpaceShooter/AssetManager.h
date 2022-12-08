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
	void CreateProjectile(Vector2 pos, Vector2 velocity, int range, int speed, std::string id);
	void CreateMeteor(Vector2 pos, Vector2 velocity, int speed, float scale, std::string id);
	void CreateRandomMeteor(Vector2 pos, std::string id);

	//textures
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

private:
	Manager* manager;
	std::map<std::string, SDL_Texture*> texture;


};


