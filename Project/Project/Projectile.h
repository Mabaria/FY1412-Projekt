#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Projectile : public sf::Drawable{
private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const = 0;

protected:
	float mass;
	float radius;
	
	sf::Vector2f velocity;
	sf::Vector2f position;
	sf::Vector2f gravity;

	

public:
	Projectile();
	~Projectile();


	virtual sf::Vector2f update() = 0; // returns new position

	float getVelocity();
	sf::Vector2f getPosition();


};

#endif
