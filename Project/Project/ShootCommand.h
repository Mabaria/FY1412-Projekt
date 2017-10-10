#pragma once
#include "Command.h"
class ShootCommand : public Command
{
public:
	ShootCommand();
	virtual void execute(bool &tapKey);
};

