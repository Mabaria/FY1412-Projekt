#ifndef ArtilleryShell_H
#define ArtilleryShell_H
#include "Projectile.h"

class ArtilleryShell :public Projectile
{
private:
	float area;
	float airDensity;
	float airViscosity;

	sf::Vector2f airSpeed;

	sf::ConvexShape triangle;
	sf::Vector2f directionVec;

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

public:
	ArtilleryShell(float airDensity, float airViscosity, sf::Vector2f position, sf::Vector2f gravity, sf::Vector2f direction, sf::Vector2f airSpeed);
	~ArtilleryShell();
	float DragCoefficient();
	sf::Vector2f DragForce(float cd);
	sf::Vector2f TotalAcceleration();
	sf::Vector2f update();
};
#endif // !ArtilleryShell_H

