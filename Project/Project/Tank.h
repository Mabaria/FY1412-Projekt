#pragma once
#ifndef TANK_H
#define TANK_H
#include "RoundProjectile.h"
#include "ArtilleryShell.h"
#include "Cube.h"
#include <SFML\Graphics.hpp>

enum PROJECTILETYPE {
	ROUNDLEFTSPIN = 0,
	ROUNDRIGHTSPIN = 1,
	ARTILLERYSHELL = 2,
	CUBE = 3,
	TOTALPROJTYPES // If new projectiles are added this NEEDS to be defined last
};

class Tank : public sf::Drawable
{
private:
	sf::RectangleShape body;
	sf::RectangleShape cannon;
	sf::CircleShape wheels[4];
	sf::FloatRect bBox;

	PROJECTILETYPE selectedProj;

	bool facingRight;
	bool myTurn;

	sf::Font dataFont;
	sf::Text dataText;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const;

public:
	Tank(sf::Vector2f pos, sf::Color color, bool facingRight);
	~Tank();

	void rotateCannon(float angle);
	bool collision(sf::FloatRect &projBounds);
	void changeProjectile();
	void shootProjectile(sf::Vector2f &gravity, sf::Vector2f &windSpeed, float airDensity, float airViscosity, Projectile* &activeProjectile);
	PROJECTILETYPE getSelectedProjectile();
	void setTurn(bool turnState);
};

#endif
