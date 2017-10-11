#pragma once
#ifndef SHOOTPROJECTILECOMMAND_H
#define SHOOTPROJECTILECOMMAND_H

#include "Command.h"
#include "Tank.h"
class ShootProjectileCommand : public Command
{
	Tank* tank;
	sf::Vector2f gravity;
	float airDensity;
	float airViscosity;
public:
	ShootProjectileCommand(Tank* tank, sf::Vector2f &gravity, float airDensity, float airViscosity);
	virtual void execute(bool &tapKey);
};

#endif // !SHOOTPROJECTILECOMMAND_H
