#ifndef CUBE_H
#define CUBE_H
#include"Projectile.h"

class Cube :public Projectile
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

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
public:

};
#endif // !CUBE_H

