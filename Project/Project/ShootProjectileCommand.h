#pragma once
#ifndef SHOOTPROJECTILECOMMAND_H
#define SHOOTPROJECTILECOMMAND_H

#include "Command.h"
#include "Tank.h"
class ShootProjectileCommand : public Command
{
	Tank* tank;

public:
	ShootProjectileCommand(Tank* tank);
	virtual void execute(bool &tapKey);
};

#endif // !SHOOTPROJECTILECOMMAND_H
