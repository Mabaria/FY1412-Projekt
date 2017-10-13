#include "ShootProjectileCommand.h"

ShootProjectileCommand::ShootProjectileCommand(Tank * tank, sf::Vector2f &gravity, sf::Vector2f &windSpeed, float airDensity, float airViscosity, Projectile** activeProjectile)
{
	this->tank = tank;
	this->gravity = gravity;
	this->windSpeed = windSpeed;
	this->airDensity = airDensity;
	this->airViscosity = airViscosity;
	this->activeProjectile = activeProjectile;
}

void ShootProjectileCommand::execute(bool & tapKey)
{
	this->tank->shootProjectile(this->gravity, this->windSpeed, this->airDensity, this->airViscosity, *this->activeProjectile);
}
