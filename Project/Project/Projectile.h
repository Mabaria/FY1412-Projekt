#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Projectile {
protected:
	float mass;
	float radius;
	float e;  // Coefficient of restitution 
	
	sf::Vector2f velocity;
	sf::Vector2f position;
	sf::Vector2f gravity;

public:
	Projectile();
	~Projectile();


	virtual sf::Vector2f update() = 0; // returns new position

	float getVelocity();
	float getPosition();

	virtual float CalculateDragCoefficient(float reynold) = 0;
};

#endif
