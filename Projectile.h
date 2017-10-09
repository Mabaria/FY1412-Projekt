#include <Vector2.hpp>

class Projectile {
private:
	unsigned float mass;
	unsigned float radius;
	unsigned float e;  // Coefficient of restitution 
	
	sf::Vector2f velocity;
	sf::Vector2f position;
	sf::Vector2f gravity;


public:
	Projectile();
	~Projectile();


	virtual sf::Vector2f update(unsigned float dt) = 0; // Recieves delta t from main class and returns new position

	float getVelocity();
	float getPosition();

	virtual unsigned float CalculateDragCoefficient(unsigned float reynold) = 0;


}

unsigned float Projectile::getPosition() {
	return this->position;
}

unsigned float Projectile::getVelocity() {
	return this->velocity;
}



