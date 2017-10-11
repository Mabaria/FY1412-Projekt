#include "ShootProjectileCommand.h"

ShootProjectileCommand::ShootProjectileCommand(Tank * tank, sf::Vector2f &gravity, float airDensity, float airViscosity, Projectile** activeProjectile)
{
	this->tank = tank;
	this->gravity = gravity;
	this->airDensity = airDensity;
	this->airViscosity = airViscosity;
	this->activeProjectile = activeProjectile;
}

void ShootProjectileCommand::execute(bool & tapKey)
{
	this->tank->shootProjectile(this->gravity, this->airDensity, this->airViscosity, *this->activeProjectile);
}
