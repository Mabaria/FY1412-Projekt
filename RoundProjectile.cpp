#include <Vector2.hpp>
#include "RoundProjectile.h"

RoundProjectile::RoundProjectile(unsigned float mass, unsigned float radius, sf::Vector2f velocity, sf::Vector2f gravity, float angleVelocity, unsigned float e,
								 unsigned float airDensity, unsigned float airViscosity) {
	this->mass = mass;
	this->radius = radius;
	this->area = radius * radius * M_PI; // TODO: Fix a working constant for Pi
	this->velocity = velocity;
	this->gravity = gravity;
	this->angleVelocity = angleVelocity;
	this->airDensity = airDensity;
	this->airViscosity = airViscosity;
}

unsigned float RoundProjectile::Reynold() {
	// Re = (airDensity * characteristic length * velocity) / airViscosity
	// characteristic length is 2*radius because the object is spherical
	return ((this->airDensity * this->radius * 2 * this->velocity) / this->airViscosity);
}

unsigned float RoundProjectile::DragCoefficient(unsigned float reynold){
	// http://pages.mtu.edu/~fmorriso/DataCorrelationForSphereDrag2016.pdf
	unsigned float cd1 = 24/reynold;
	unsigned float cd2 = (2.6*(reynold*0.2)) / (1 + pow((reynold*0.2), 1.52));
	unsigned float cd3 = (0.411*pow(reynold/263000,-7.94)) / (1 + pow(reynold/263000,-8));
	unsigned float cd4 = (0.00000025 * reynold) / (1 + 0.000001*reynold);

	return (cd1 + cd2 + cd3 + cd4);
}

sf::Vector2f RoundProjectile::DragForce(unsigned float cd) {
	// Fd = -0.5 * Cd * airDensity * area * speed^2
	float speed = sqrt(pow(this->velocity.x, 2) + pow(this->velocity.y, 2));
	float force = -0.5 * cd * this->airDensity * this->area * pow(speed, 2);
	return sf::Vector2f((this->velocity.x / speed) * force, (this->velocity.y / speed) * force); // This returns the air resistance force vector, direction will be opposite the velocity vector
}

sf::Vector2f RoundProjectile::MagnusForce() {
	float speed = sqrt(pow(this->velocity.x, 2) + pow(this->velocity.y, 2));
	float cm = (this->radius * this->angleVelocity) / speed; // Magnus coefficient for spherical objects
	float force = 0.5 * cm * this->airDensity * pow(speed, 2) * this->area;
	return sf::Vector2f(-(this->velocity.y / speed) * force, (this->velocity.x / speed) * force); 
	// Velocity vector rotated 90 degrees, force determines positive or negative direction
	// 90 degree 2D rotation, (a, b) = (-b, a)
}

sf::Vector2f RoundProjectile::TotalAcceleration() {
	sf::Vector2f forceVector = this->DragForce(this->DragCoefficient(this->Reynold())) + this->MagnusForce();
	// F/m = a, apply to forceVector and add gravity acceleration
	return sf::Vector2f((forceVector.x / this->mass) + this->gravity.x, (forceVector.y / this->mass) + this->gravity.y); 
}

sf::Vector2f RoundProjectile::update(unsigned float dt) {
	sf::Vector2f acceleration = this->TotalAcceleration(); // This function calls and calculates all forces currently affecting the object and returns an acceleration vector
	// r = r0 + vt + at^2 / 2
	sf::Vector2f newPos = sf::Vector2f(this->position.x + this->velocity * dt + (this->acceleration * pow(dt, 2)) / 2);
	// v = v0 + at
	this->velocity = this->velocity + acceleration * dt;
}