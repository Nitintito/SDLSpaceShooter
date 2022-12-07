#include "AssetManager.h"
#include "Components.h"

AssetManager::AssetManager(Manager* manager) : manager(manager)
{
}

AssetManager::~AssetManager()
{}

void AssetManager::CreateProjectile(Vector2 pos, int range, int speed, std::string id)
{
	auto& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 16, 16, 0.3);
	projectile.addComponent<SpriteComponent>("projectile");
	projectile.addComponent<ProjectileComponent>(range, speed);
	projectile.addComponent<ColliderComponent>("projectile");
}	


void AssetManager::AddTexture(std::string id, const char* path)
{
	texture.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return texture[id];
}


