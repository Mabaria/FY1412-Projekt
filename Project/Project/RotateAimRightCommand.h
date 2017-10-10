#pragma once
#include "Command.h"
class RotateAimRightCommand : public Command
{
public:
	RotateAimRightCommand();
	virtual void execute(bool &tapKey);
};

