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


	virtual sf::Vector2f update(float dt) = 0; // Recieves delta t from main class and returns new position

	float getVelocity();
	float getPosition();

	virtual float CalculateDragCoefficient(float reynold) = 0;


};