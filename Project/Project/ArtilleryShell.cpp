#include "ArtilleryShell.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Locator.h"

#define ARTILLERYPROJMASS 80
#define ARTILLERYPROJVELOCITY 150
#define ARTILLERYPROJRADIUS 0.40f
//#define ROUNDPROJANGLEVELOCITY -0.00f 



ArtilleryShell::ArtilleryShell(float airDensity, float airViscosity, sf::Vector2f position, sf::Vector2f gravity, sf::Vector2f direction, sf::Vector2f airSpeed)
{
	this->mass = ARTILLERYPROJMASS;
	this->radius = ARTILLERYPROJRADIUS;
	this->area = this->radius*this->radius*(float)M_PI;
	this->position = position;
	this->velocity = sf::Vector2f(direction.x*ARTILLERYPROJVELOCITY, direction.y*ARTILLERYPROJVELOCITY);
	this->gravity = sf::Vector2f(gravity.x*ARTILLERYPROJMASS, gravity.y*ARTILLERYPROJMASS);
	this->airDensity = airDensity;
	this->airViscosity = airViscosity;

	this->triangle.setPointCount(3);
	this->triangle.setPoint(0, sf::Vector2f(0.f, 0.f));
	this->triangle.setPoint(1, sf::Vector2f(0.f, 5.f));
	this->triangle.setPoint(2, sf::Vector2f(5.f, 2.5f));
	this->triangle.setFillColor(sf::Color::Black);
	this->triangle.setOrigin(5.f / 3.f, 2.5f);
	this->triangle.setPosition(this->position);
	//this->directionVec=sf::Vector2f((this->position.x+2,5)-(this->position.x),((this->position.y-2.5)))
	this->triangle.rotate(-atanf(this->velocity.y / this->velocity.x));


}

ArtilleryShell::~ArtilleryShell()
{
}

void ArtilleryShell::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->triangle);
}

float ArtilleryShell::DragCoefficient()
{
	float cd = -1;
	float speed = sqrt(pow(this->velocity.x, 2) + pow(this->velocity.y, 2));
	if (speed < 340)
	{
		cd = 0.12;
	}
	else
	{
		cd = 0.41 * 340 - ((0.25 * 340 / 4)*speed);
	}

	return cd;
}

sf::Vector2f ArtilleryShell::DragForce(float cd)
{
	float speed = sqrt(pow(this->velocity.x, 2) + pow(this->velocity.y, 2));
	sf::Vector2f dragForce;
	if (speed < 0.5f)
		dragForce = sf::Vector2f(0.0f, 0.0f);
	float force = -0.5f*cd*this->airDensity*this->area*pow(speed, 2);
	dragForce = sf::Vector2f((this->velocity.x / speed)*force, (this->velocity.y / speed)*force);

	return dragForce;
}

sf::Vector2f ArtilleryShell::TotalAcceleration()
{
	sf::Vector2f dragForce = this->DragForce(this->DragCoefficient());
	sf::Vector2f forceVector = dragForce + this->gravity;

	return sf::Vector2f((forceVector.x / this->mass), (forceVector.y / this->mass));
}

sf::Vector2f ArtilleryShell::update()
{
	sf::Vector2f acceleration = this->TotalAcceleration();
	float dt = 3.0f*Locator::getGameTime()->getDeltaTime();

	sf::Vector2f newPos = sf::Vector2f((this->position.x + (this->velocity.x*dt) + ((acceleration.x*pow(dt, 2)) / 2)), (this->position.y + (this->velocity.y*dt) + ((acceleration.y*pow(dt, 2)) / 2)));
	this->velocity = this->velocity + (acceleration*dt);
	this->position = newPos;
	this->triangle.setPosition(this->position);
	this->triangle.setRotation(-atanf(this->velocity.y / this->velocity.x));
	return sf::Vector2f();
}