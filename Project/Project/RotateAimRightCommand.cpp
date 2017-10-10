#include "RotateAimRightCommand.h"



RotateAimRightCommand::RotateAimRightCommand(Tank* tank)
{
	this->tank = tank;
}

void RotateAimRightCommand::execute(bool & tapKey)
{
	this->tank->rotateCannon(10);
}
