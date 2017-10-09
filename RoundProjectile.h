#include "Projectile.h"

class RoundProjectile : public Projectile {
private:
	float area;
	float angleVelocity; // rad/s, positive value means counter clockwise spin
	float airDensity;
	float airViscosity;


public:

	RoundProjectile(unsigned float mass, unsigned float radius, sf::Vector2f velocity, sf::Vector2f gravity, float angleVelocity, unsigned float e,
					unsigned float airDensity, unsigned float airViscosity);
	~RoundProjectile();
	unsigned float Reynold();
	unsigned float DragCoefficient(unsigned float reynold);
	sf::Vector2f DragForce(unsigned float cd);
	sf::Vector2f MagnusForce();
	sf::Vector2f TotalAcceleration();
	sf::Vector2f update(unsigned float dt);
}