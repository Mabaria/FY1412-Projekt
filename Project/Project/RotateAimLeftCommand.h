#pragma once
#ifndef ROTATEAIMLEFTCOMMAND_H
#define ROTATEAIMLEFTCOMMAND_H

#include "Command.h"
#include "Tank.h"

class RotateAimLeftCommand : public Command
{
	Tank* tank;
public:
	RotateAimLeftCommand(Tank* tank);
	virtual void execute(bool &tapKey);
};

#endif
