#include "AssetManager.h"
#include "Components.h"

AssetManager::AssetManager(Manager* man) : manager(man)
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
	projectile.addComponent<ColliderComponent>(id);
	projectile.addGroup(Game::groupProjectiles);
	//std::cout << "Create Projectile!" << std::endl;
}
void AssetManager::CreateMeteor(Vector2 pos, Vector2 velocity, int speed, float scale, std::string id)
{
	auto& meteor(manager->addEntity());
	meteor.addComponent<TransformComponent>(pos.x, pos.y);
	meteor.addComponent<SpriteComponent>(id);
	meteor.addComponent<MeteorComponent>(scale, speed, velocity);
	meteor.addComponent<ColliderComponent>(id);
	meteor.addGroup(Game::groupMeteors);
}

void AssetManager::CreateRandomMeteor(Vector2 pos, std::string id)
{
	auto& meteor(manager->addEntity());
	meteor.addComponent<TransformComponent>(pos.x, pos.y);
	meteor.addComponent<SpriteComponent>(id);
	meteor.addComponent<MeteorComponent>(true);
	meteor.addComponent<ColliderComponent>(id);
	meteor.addGroup(Game::groupMeteors);

}

void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}


