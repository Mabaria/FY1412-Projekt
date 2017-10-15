#pragma once
#ifndef CHANGEPROJECTILECOMMAND_H
#define CHANGEPROJECTILECOMMAND_H

#include "Command.h"
#include "Tank.h"

class ChangeProjectileCommand : public Command
{
private:
	Tank* tank1;
	Tank* tank2;

public:
	ChangeProjectileCommand(Tank* tank1, Tank* tank2);
	virtual void execute(bool& tapKey);
};

#endif // !CHANGEPROJECTILECOMMAND_H
