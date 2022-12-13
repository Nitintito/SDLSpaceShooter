#include "KeyboardController.h"


void KeyboardController::Shoot()
{
	Game::assetManager->CreateProjectile(Vector2(400, 400), Vector2(0, -1), 800, 5, "Projectile");

}
