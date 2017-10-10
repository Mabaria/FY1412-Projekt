#pragma once
#include "Command.h"
class RotateAimLeftCommand : public Command
{
public:
	RotateAimLeftCommand();
	virtual void execute(bool &tapKey);
};

