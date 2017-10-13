#include "Projectile.h"

Projectile::Projectile()
{
}

Projectile::~Projectile()
{
}

sf::Vector2f Projectile::getVelocity()
{
	return this->velocity;
}

sf::Vector2f Projectile::getPosition()
{
	return this->position;
}
