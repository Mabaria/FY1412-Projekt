#include "Projectile.h"

enum ROUNDSPINDIRECTION {
	ROUNDSPINLEFT = 0,
	ROUNDSPINRIGHT = 1
};

class RoundProjectile : public Projectile {
private:
	float area;
	float angleVelocity; // rad/s, positive value means counter clockwise spin
	float airDensity;
	float airViscosity;
	float momOfInertia;

	sf::Vector2f windSpeed;

	sf::CircleShape sphere;
	sf::Font dataFont;
	sf::Text dataText;

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	float ViscousTorque(); // Returns the angular acceleration due to viscous torque
public:

	RoundProjectile(float airDensity, float airViscosity, sf::Vector2f position, sf::Vector2f gravity, sf::Vector2f direction, ROUNDSPINDIRECTION spinDir, sf::Vector2f windSpeed);
	~RoundProjectile();
	 float Reynold();
	 float DragCoefficient( float reynold);
	sf::Vector2f DragForce( float cd);
	sf::Vector2f MagnusForce();
	sf::Vector2f TotalAcceleration();
	sf::Vector2f update();
	virtual sf::FloatRect getBoundingBox();
};