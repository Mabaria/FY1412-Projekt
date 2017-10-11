#include "ChangeProjectileCommand.h"



ChangeProjectileCommand::ChangeProjectileCommand(Tank* tank)
{
	this->tank = tank;
}

void ChangeProjectileCommand::execute(bool & tapKey)
{
	this->tank->changeProjectile();
}
