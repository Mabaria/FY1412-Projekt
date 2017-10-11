#include "ShootProjectileCommand.h"

ShootProjectileCommand::ShootProjectileCommand(Tank * tank)
{
	this->tank = tank;
}

void ShootProjectileCommand::execute(bool & tapKey)
{
	this->tank->shootProjectile();
}
