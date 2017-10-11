#include "ShootProjectileCommand.h"

ShootProjectileCommand::ShootProjectileCommand(Tank * tank, sf::Vector2f &gravity, float airDensity, float airViscosity)
{
	this->tank = tank;
	this->gravity = gravity;
	this->airDensity = airDensity;
	this->airViscosity = airViscosity;

}

void ShootProjectileCommand::execute(bool & tapKey)
{
	this->tank->shootProjectile(this->gravity, this->airDensity, this->airViscosity);
}
