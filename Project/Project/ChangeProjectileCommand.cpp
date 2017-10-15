#include "ChangeProjectileCommand.h"



ChangeProjectileCommand::ChangeProjectileCommand(Tank* tank1, Tank* tank2)
{
	this->tank1 = tank1;
	this->tank2 = tank2;
}

void ChangeProjectileCommand::execute(bool & tapKey)
{
	tapKey = true;
	this->tank1->changeProjectile();
	this->tank2->changeProjectile();
}
