#pragma once
#ifndef SHOOTPROJECTILECOMMAND_H
#define SHOOTPROJECTILECOMMAND_H

#include "Command.h"
#include "Tank.h"

class ShootProjectileCommand : public Command
{
	Tank* tank;
	Projectile** activeProjectile;
	sf::Vector2f gravity;
	sf::Vector2f windSpeed;
	float airDensity;
	float airViscosity;

public:
	ShootProjectileCommand(Tank* tank, sf::Vector2f &gravity, sf::Vector2f &windSpeed, float airDensity, float airViscosity, Projectile** activeProjectile);
	virtual void execute(bool &tapKey);
};

#endif // !SHOOTPROJECTILECOMMAND_H
