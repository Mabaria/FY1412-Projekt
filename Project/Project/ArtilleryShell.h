#ifndef ArtilleryShell_H
#define ArtilleryShell_H
#include "Projectile.h"

class ArtilleryShell :public Projectile
{
private:
	float area;
	float airDensity;
	float airViscosity;

	sf::Vector2f windSpeed;

	sf::ConvexShape triangle;
	sf::Vector2f directionVec;
	sf::Font dataFont;
	sf::Text dataText;

	sf::RectangleShape gravityLine;
	sf::RectangleShape dragForceLine;

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void updateLines();
public:
	ArtilleryShell(float airDensity, float airViscosity, sf::Vector2f position, sf::Vector2f gravity, sf::Vector2f direction, sf::Vector2f windSpeed);
	~ArtilleryShell();
	float DragCoefficient();
	sf::Vector2f DragForce(float cd);
	sf::Vector2f TotalAcceleration();
	sf::Vector2f update();
	virtual sf::FloatRect getBoundingBox();
};
#endif // !ArtilleryShell_H

