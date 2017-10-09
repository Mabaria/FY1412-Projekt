#include "Projectile.h"

class RoundProjectile : public Projectile {
private:
	float area;
	float angleVelocity; // rad/s, positive value means counter clockwise spin
	float airDensity;
	float airViscosity;


public:

	RoundProjectile( float mass,  float radius, sf::Vector2f velocity, sf::Vector2f gravity, float angleVelocity,  float e,
					 float airDensity,  float airViscosity);
	~RoundProjectile();
	 float Reynold();
	 float DragCoefficient( float reynold);
	sf::Vector2f DragForce( float cd);
	sf::Vector2f MagnusForce();
	sf::Vector2f TotalAcceleration();
	sf::Vector2f update( float dt);
};