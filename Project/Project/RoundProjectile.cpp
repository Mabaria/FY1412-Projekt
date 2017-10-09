#include "RoundProjectile.h"
#define _USE_MATH_DEFINES
#include <math.h>

RoundProjectile::RoundProjectile( float mass,  float radius, sf::Vector2f velocity, sf::Vector2f gravity, float angleVelocity,  float e,
								  float airDensity,  float airViscosity) {
	this->mass = mass;
	this->radius = radius;
	this->area = radius * radius * (float)M_PI; // TODO: Fix a working constant for Pi
	this->velocity = velocity;
	this->gravity = gravity;
	this->angleVelocity = angleVelocity;
	this->airDensity = airDensity;
	this->airViscosity = airViscosity;
}

RoundProjectile::~RoundProjectile() {

}

 float RoundProjectile::Reynold() {
	// Re = (airDensity * characteristic length * velocity) / airViscosity
	// characteristic length is 2*radius because the object is spherical
	 float speed = sqrt(pow(this->velocity.x, 2) + pow(this->velocity.y, 2));
	return ((this->airDensity * this->radius * 2 * speed) / this->airViscosity);
}

 float RoundProjectile::DragCoefficient( float reynold){
	// http://pages.mtu.edu/~fmorriso/DataCorrelationForSphereDrag2016.pdf
	 float cd1 = 24/reynold;
	 float cd2 = (2.6f*(reynold*0.2f)) / (1 + pow((reynold*0.2f), 1.52f));
	 float cd3 = (0.411f*pow(reynold/263000,-7.94f)) / (1 + pow(reynold/263000,-8));
	 float cd4 = (0.00000025f * reynold) / (1 + 0.000001f*reynold);

	return (cd1 + cd2 + cd3 + cd4);
}

sf::Vector2f RoundProjectile::DragForce( float cd) {
	// Fd = -0.5 * Cd * airDensity * area * speed^2
	float speed = sqrt(pow(this->velocity.x, 2) + pow(this->velocity.y, 2));
	float force = -0.5f * cd * this->airDensity * this->area * pow(speed, 2);
	return sf::Vector2f((this->velocity.x / speed) * force, (this->velocity.y / speed) * force); // This returns the air resistance force vector, direction will be opposite the velocity vector
}

sf::Vector2f RoundProjectile::MagnusForce() {
	float speed = sqrt(pow(this->velocity.x, 2) + pow(this->velocity.y, 2));
	float cm = (this->radius * this->angleVelocity) / speed; // Magnus coefficient for spherical objects
	float force = 0.5f * cm * this->airDensity * pow(speed, 2) * this->area;
	return sf::Vector2f(-(this->velocity.y / speed) * force, (this->velocity.x / speed) * force); 
	// Velocity vector rotated 90 degrees, force determines positive or negative direction
	// 90 degree 2D rotation, (a, b) = (-b, a)
}

sf::Vector2f RoundProjectile::TotalAcceleration() {
	sf::Vector2f forceVector = this->DragForce(this->DragCoefficient(this->Reynold())) + this->MagnusForce();
	// F/m = a, apply to forceVector and add gravity acceleration
	return sf::Vector2f((forceVector.x / this->mass) + this->gravity.x, (forceVector.y / this->mass) + this->gravity.y); 
}

sf::Vector2f RoundProjectile::update(float dt) {
	sf::Vector2f acceleration = this->TotalAcceleration(); // This function calls and calculates all forces currently affecting the object and returns an acceleration vector
	// r = r0 + vt + at^2 / 2
	sf::Vector2f newPos = sf::Vector2f((this->position.x + (this->velocity.x * dt) + ((acceleration.x * pow(dt, 2)) / 2)),
									   (this->position.y + (this->velocity.y * dt) + ((acceleration.y * pow(dt, 2)) / 2)) );
	// v = v0 + at
	this->velocity = this->velocity + acceleration * dt;
	return newPos;
}