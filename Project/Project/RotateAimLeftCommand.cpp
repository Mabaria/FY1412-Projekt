#include "RotateAimLeftCommand.h"



RotateAimLeftCommand::RotateAimLeftCommand(Tank* tank)
{
	this->tank = tank;
}

void RotateAimLeftCommand::execute(bool & tapKey)
{
	this->tank->rotateCannon(-10.0f);
}
