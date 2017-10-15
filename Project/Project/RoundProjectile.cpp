#include "RoundProjectile.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Locator.h"

#define ROUNDPROJMASS 200
#define ROUNDPROJVELOCITY 200
#define ROUNDPROJRADIUS 0.40f
#define ROUNDPROJANGLEVELOCITY 50.00f 

RoundProjectile::RoundProjectile(float airDensity, float airViscosity, sf::Vector2f position, sf::Vector2f gravity, sf::Vector2f direction, ROUNDSPINDIRECTION spinDir, sf::Vector2f windSpeed) {
	this->mass = ROUNDPROJMASS;
	this->radius = ROUNDPROJRADIUS;
	this->momOfInertia = 0.4f * this->mass * pow(this->radius, 2);
	this->position = position;
	this->area = this->radius * this->radius * (float)M_PI; 
	this->velocity = sf::Vector2f(direction.x * ROUNDPROJVELOCITY, direction.y * ROUNDPROJVELOCITY);
	this->gravity = sf::Vector2f(gravity.x*ROUNDPROJMASS, gravity.y*ROUNDPROJMASS);
	this->windSpeed = windSpeed;

	if (spinDir == ROUNDSPINLEFT)
		this->angleVelocity = -ROUNDPROJANGLEVELOCITY;
	else
		this->angleVelocity = ROUNDPROJANGLEVELOCITY;
	this->airDensity = airDensity;
	this->airViscosity = airViscosity;

	this->sphere.setFillColor(sf::Color::Black);
	this->sphere.setRadius(5.0f);
	this->sphere.setPosition(this->position);
	this->sphere.setOrigin(sf::Vector2f(ROUNDPROJRADIUS / 2, ROUNDPROJRADIUS / 2));

	this->dataFont.loadFromFile("Resources\\Fonts\\arial.ttf");
	this->dataText.setFont(this->dataFont);
	this->dataText.setCharacterSize(12);

	this->dataText.setString("Drag force: 0");
	this->dataText.setOrigin(sf::Vector2f(this->dataText.getGlobalBounds().left + this->dataText.getGlobalBounds().width, 0.0f));
	this->dataText.setPosition(sf::Vector2f(1000.0f, 200.0f));
}

RoundProjectile::~RoundProjectile() {

}

void RoundProjectile::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(this->sphere);
	target.draw(this->dataText);
}

float RoundProjectile::ViscousTorque()
{

	float vTorque = -8 * M_PI * pow(this->radius, 3) * this->airViscosity * this->angleVelocity;
	// Angular acceleration = torque / I
	float angAcc = vTorque / this->momOfInertia;
	return angAcc;
}

 float RoundProjectile::Reynold() {
	// Re = (airDensity * characteristic length * velocity) / airViscosity
	// characteristic length is 2*radius because the object is spherical
	float speed = sqrt(pow(this->velocity.x, 2) + pow(this->velocity.y, 2));
	return ((this->airDensity * this->radius * 2 * speed) / this->airViscosity);
}

 float RoundProjectile::DragCoefficient( float reynold){
	// http://pages.mtu.edu/~fmorriso/DataCorrelationForSphereDrag2016.pdf
	 float cd1, cd2, cd3, cd4, cdtotal;

	 if (reynold < 4.0f)
		 cdtotal = 24 / reynold;
	 else {
		 cd1 = 24 / reynold;
		 cd2 = (2.6f*(reynold*0.2f)) / (1 + pow((reynold*0.2f), 1.52f));
		 cd3 = (0.411f*pow(reynold / 263000, -7.94f)) / (1 + pow(reynold / 263000, -8));
		 cd4 = (0.00000025f * reynold) / (1 + 0.000001f*reynold);
		 cdtotal = cd1 + cd2 + cd3 + cd4;
	 }


	 return cdtotal;
}

sf::Vector2f RoundProjectile::DragForce( float cd) {
	sf::Vector2f relativeSpeed = this->velocity - this->windSpeed;
	// Fd = -0.5 * Cd * airDensity * area * speed^2
	float speed = sqrt(pow(relativeSpeed.x, 2) + pow(relativeSpeed.y, 2));
	if (speed < 0.5f) {
		return sf::Vector2f(0.0f, 0.0f);
	}
	float force = -0.5f * cd * this->airDensity * this->area * pow(speed, 2);
	return sf::Vector2f((relativeSpeed.x / speed) * force, (relativeSpeed.y / speed) * force); // This returns the air resistance force vector, direction will be opposite the velocity vector
}

sf::Vector2f RoundProjectile::MagnusForce() {
	float speed = sqrt(pow(this->velocity.x, 2) + pow(this->velocity.y, 2));
	if (speed < 0.5f) {
		return sf::Vector2f(0.0f, 0.0f);
	}
	float cm = (this->radius * this->angleVelocity) / speed; // Magnus coefficient for spherical objects
	float force = 0.5f * cm * this->airDensity * pow(speed, 2) * this->area;
	return sf::Vector2f(-(this->velocity.y / speed) * force, (this->velocity.x / speed) * force); 
	// Velocity vector rotated 90 degrees, force determines positive or negative direction
	// 90 degree 2D rotation, (a, b) = (-b, a)
}

sf::Vector2f RoundProjectile::TotalAcceleration() {
	sf::Vector2f dragForce = this->DragForce(this->DragCoefficient(this->Reynold()));
	sf::Vector2f forceVector = dragForce + this->MagnusForce() + this->gravity;
	this->dataText.setString("Drag force: " + std::to_string((int)round(sqrt(pow(dragForce.x, 2) + pow(dragForce.y, 2)))) +
		"\nReynold: " + std::to_string((int)round(this->Reynold())) +
		"\nCD: " + std::to_string(this->DragCoefficient(this->Reynold())) +
		"\nVelocity: " + std::to_string(sqrt(pow(this->velocity.x, 2) + pow(this->velocity.y, 2))) +
		"\nAngleVelocity: " + std::to_string(this->angleVelocity));
	// F/m = a, apply to forceVector and add gravity acceleration
	return sf::Vector2f((forceVector.x / this->mass), (forceVector.y / this->mass)); 
}

sf::Vector2f RoundProjectile::update() {
	sf::Vector2f acceleration = this->TotalAcceleration(); // This function calls and calculates all forces currently affecting the object and returns an acceleration vector
	// r = r0 + vt + at^2 / 2
	float dt = 3.0f * Locator::getGameTime()->getDeltaTime();

	sf::Vector2f newPos = sf::Vector2f((this->position.x + (this->velocity.x * dt) + ((acceleration.x * pow(dt, 2)) / 2)),
									   (this->position.y + (this->velocity.y * dt) + ((acceleration.y * pow(dt, 2)) / 2)) );
	// v = v0 + at
	this->velocity = this->velocity + acceleration * dt;
	this->angleVelocity = this->angleVelocity + dt * this->ViscousTorque();
	this->position = newPos;
	this->sphere.setPosition(this->position);
	return newPos;
}

sf::FloatRect RoundProjectile::getBoundingBox()
{
	return this->sphere.getGlobalBounds();
}
