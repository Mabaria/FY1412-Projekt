#pragma once
#ifndef CHANGEPROJECTILECOMMAND_H
#define CHANGEPROJECTILECOMMAND_H

#include "Command.h"
#include "Tank.h"

class ChangeProjectileCommand : public Command
{
private:
	Tank* tank;

public:
	ChangeProjectileCommand(Tank* tank);
	virtual void execute(bool& tapKey);
};

#endif // !CHANGEPROJECTILECOMMAND_H
