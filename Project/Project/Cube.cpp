#include "Cube.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Locator.h"

#define CUBEMASS 200
#define CUBEVELOCITY 160
#define CUBERADIUS 0.40f


Cube::Cube(float airDensity, float airViscosity, sf::Vector2f position, sf::Vector2f gravity, sf::Vector2f direction, sf::Vector2f windSpeed)
{
	this->mass = CUBEMASS;
	this->radius = CUBERADIUS;
	this->area = this->radius*this->radius;
	this->position = position;
	this->velocity = sf::Vector2f(direction.x*CUBEVELOCITY, direction.y*CUBEVELOCITY);
	this->gravity = sf::Vector2f(gravity.x*CUBEMASS, gravity.y*CUBEMASS);
	this->airDensity = airDensity;
	this->airViscosity = airViscosity;
	this->windSpeed = windSpeed;

	this->dataFont.loadFromFile("Resources\\Fonts\\arial.ttf");
	this->dataText.setFont(this->dataFont);
	this->dataText.setCharacterSize(12);

	this->dataText.setString("Drag force: 0");
	this->dataText.setOrigin(sf::Vector2f(this->dataText.getGlobalBounds().left + this->dataText.getGlobalBounds().width, 0.0f));
	this->dataText.setPosition(sf::Vector2f(1000.0f, 200.0f));

	this->cube.setSize(sf::Vector2f(CUBERADIUS, CUBERADIUS));
	this->cube.setOrigin(sf::Vector2f(CUBERADIUS / 2, CUBERADIUS / 2));
	this->cube.setFillColor(sf::Color::Black);
	this->cube.setPosition(this->position);
	this->cube.rotate((180.0f / (float)M_PI) *atan2f(this->velocity.y, this->velocity.x));
}

Cube::~Cube()
{

}

float Cube::Reynold()
{
	return ((this->airDensity*this->radius*(sqrt(pow(this->velocity.x, 2) + pow(this->velocity.y, 2)))) / this->airViscosity);
}

float Cube::DragCoefficient(float re)//https://www.calpoly.edu/~kshollen/ME347/Handouts/Friction_Drag_Coef.pdf
{
	float cd = 0.f;
	if (re < 500000.f)
	{
		cd = 1.328f*pow(re, -0.5f);
	}
	else if (re < 1000000000.f)
	{
		cd = ((0.455f / (pow(log(re), 2.58f))) - (1700 / re));
	}
	else
		cd = (pow(1.89f - (1.62f*log(0.015 / this->radius)), -2.5f));

	return cd;
}

sf::Vector2f Cube::DragForce(float cd)
{
	sf::Vector2f relativeSpeed = this->velocity - this->windSpeed;
	float speed = sqrt(pow(relativeSpeed.x, 2) + pow(relativeSpeed.y, 2));
	if (speed < 0.5f) {
		return sf::Vector2f(0.0f, 0.0f);
	}
	float force = -0.5f * cd * this->airDensity * this->area * pow(speed, 2);
	return sf::Vector2f((relativeSpeed.x / speed) * force, (relativeSpeed.y / speed) * force);
}

sf::Vector2f Cube::TotalAcceleration()
{
	sf::Vector2f dragForce = this->DragForce(this->DragCoefficient(this->Reynold()));
	sf::Vector2f forceVector = dragForce + this->gravity;
	this->dataText.setString("Drag force: " + std::to_string((int)round(sqrt(pow(dragForce.x, 2) + pow(dragForce.y, 2)))) +
		"\nReynold: " + std::to_string((int)round(this->Reynold())) +
		"\nCD: " + std::to_string(this->DragCoefficient(this->Reynold())) +
		"\nVelocity: " + std::to_string(sqrt(pow(this->velocity.x, 2) + pow(this->velocity.y, 2))));
	// F/m = a, apply to forceVector and add gravity acceleration
	return sf::Vector2f((forceVector.x / this->mass), (forceVector.y / this->mass));
}

sf::Vector2f Cube::update()
{
	sf::Vector2f acceleration = this->TotalAcceleration(); // This function calls and calculates all forces currently affecting the object and returns an acceleration vector
														   // r = r0 + vt + at^2 / 2
	float dt = 3.0f * Locator::getGameTime()->getDeltaTime();

	sf::Vector2f newPos = sf::Vector2f((this->position.x + (this->velocity.x * dt) + ((acceleration.x * pow(dt, 2)) / 2)),
		(this->position.y + (this->velocity.y * dt) + ((acceleration.y * pow(dt, 2)) / 2)));
	// v = v0 + at
	this->velocity = this->velocity + acceleration * dt;
	this->position = newPos;
	this->cube.setPosition(this->position);
	this->cube.rotate((180.0f / (float)M_PI) *atan2f(this->velocity.y, this->velocity.x));
	return newPos;
}

sf::FloatRect Cube::getBoundingBox()
{
	return this->cube.getGlobalBounds();
}

