#pragma once
#ifndef ROTATEAIMRIGHTCOMMAND_H
#define ROTATEAIMRIGHTCOMMAND_H

#include "Command.h"
#include "Tank.h"

class RotateAimRightCommand : public Command
{
private:
	Tank* tank;
public:
	RotateAimRightCommand(Tank* tank);
	virtual void execute(bool &tapKey);
};

#endif
