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

	sf::RectangleShape cube;
	sf::Vector2f directionVec;
	sf::Font dataFont;
	sf::Text dataText;

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
public:
	Cube(float airDensity, float airViscosity, sf::Vector2f position, sf::Vector2f gravity, sf::Vector2f direction, sf::Vector2f windSpeed);
	~Cube();
	float Reynold();
	float DragCoefficient(float re);
	sf::Vector2f DragForce(float cd);
	sf::Vector2f TotalAcceleration();
	sf::Vector2f update();
	virtual sf::FloatRect getBoundingBox();

};
#endif // !CUBE_H

