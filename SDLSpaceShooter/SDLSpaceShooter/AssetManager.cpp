#include "AssetManager.h"
#include "Components.h"

AssetManager::AssetManager(Manager* manager) : manager(manager)
{
}

AssetManager::~AssetManager()
{}

void AssetManager::CreateProjectile(Vector2 pos, Vector2 velocity, int range, int speed, std::string id)
{
	auto& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 8, 8, 0.7);
	projectile.addComponent<SpriteComponent>(id);
	projectile.addComponent<ProjectileComponent>(range, speed, velocity);
	projectile.addComponent<ColliderComponent>("projectile");
	projectile.addGroup(Game::groupProjectiles);
	std::cout << "Shooting projectile!" << endl;
}
void AssetManager::CreateMeteor(Vector2 pos, Vector2 velocity, int speed, float scale, std::string id)
{
	auto& meteor(manager->addEntity());
	meteor.addComponent<TransformComponent>(pos.x, pos.y, scale).velocity = velocity * speed;
	meteor.addComponent<SpriteComponent>("Meteor");
	meteor.addComponent<ColliderComponent>("Meteor");
	meteor.addGroup(Game::groupMeteors);

	std::cout << "Spwaning Meteor" << endl;
}


void AssetManager::AddTexture(std::string id, const char* path)
{
	texture.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return texture[id];
}


