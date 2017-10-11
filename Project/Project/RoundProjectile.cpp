#include "RoundProjectile.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Locator.h"

#define ROUNDPROJMASS 25
#define ROUNDPROJVELOCITY 119
#define ROUNDPROJRADIUS 0.10f
#define ROUNDPROJANGLEVELOCITY 62.831f // 10 revolutions per second

RoundProjectile::RoundProjectile(float airDensity, float airViscosity, sf::Vector2f position, sf::Vector2f gravity, sf::Vector2f direction) {
	this->mass = ROUNDPROJMASS;
	this->radius = ROUNDPROJRADIUS;
	this->position = position;
	this->area = this->radius * this->radius * (float)M_PI; 
	this->velocity = sf::Vector2f(direction.x * ROUNDPROJVELOCITY, direction.y * ROUNDPROJVELOCITY);
	this->gravity = gravity;
	this->angleVelocity = ROUNDPROJANGLEVELOCITY;
	this->airDensity = airDensity;
	this->airViscosity = airViscosity;

	this->sphere.setFillColor(sf::Color::Black);
	this->sphere.setRadius(10.0f);
	this->sphere.setPosition(this->position);
}

RoundProjectile::~RoundProjectile() {

}

void RoundProjectile::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(this->sphere);
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

sf::Vector2f RoundProjectile::update() {
	sf::Vector2f acceleration = this->TotalAcceleration(); // This function calls and calculates all forces currently affecting the object and returns an acceleration vector
	// r = r0 + vt + at^2 / 2
	float dt = Locator::getGameTime()->getDeltaTime();

	sf::Vector2f newPos = sf::Vector2f((this->position.x + (this->velocity.x * dt) + ((acceleration.x * pow(dt, 2)) / 2)),
									   (this->position.y + (this->velocity.y * dt) + ((acceleration.y * pow(dt, 2)) / 2)) );
	// v = v0 + at
	this->velocity = this->velocity + acceleration * dt;
	this->position = newPos;
	this->sphere.setPosition(this->position);
	return newPos;
}