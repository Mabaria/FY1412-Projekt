#include "Cube.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Locator.h"

#define CUBEMASS 50
#define CUBEVELOCITY 560
#define CUBERADIUS 0.40f


void Cube::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->cube);
	target.draw(this->dataText);
	target.draw(this->gravityLine);
	target.draw(this->dragForceLine);
}

void Cube::updateLines()
{
	// This is a quick and dirty implementation, a good one would only calculate these
	// values once but at this point I just want a nice working solution
	this->gravityLine.setPosition(this->position);
	this->dragForceLine.setPosition(this->position);
	sf::Vector2f gravityForceVector = this->gravity;
	sf::Vector2f dragForceVector = this->DragForce(this->DragCoefficient());
	float totalVectorLength = (sqrt(pow(gravityForceVector.x, 2) + pow(gravityForceVector.y, 2)) +
		sqrt(pow(dragForceVector.x, 2) + pow(dragForceVector.y, 2)));

	float gravityLineLength = sqrt(pow(gravityForceVector.x, 2) + pow(gravityForceVector.y, 2)) / totalVectorLength;
	float dragLineLength = sqrt(pow(dragForceVector.x, 2) + pow(dragForceVector.y, 2)) / totalVectorLength;

	this->gravityLine.setSize(sf::Vector2f(gravityLineLength * 200.0f, 2));
	this->dragForceLine.setSize(sf::Vector2f(dragLineLength * 200.0f, 2));

	this->gravityLine.setRotation((180.0f / M_PI) * atan2f(gravityForceVector.y, gravityForceVector.x));
	this->dragForceLine.setRotation((180.0f / M_PI) * atan2f(dragForceVector.y, dragForceVector.x));

}

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

	this->cube.setSize(sf::Vector2f(10, 10));
	this->cube.setOrigin(sf::Vector2f(5, 5));
	this->cube.setFillColor(sf::Color::Black);
	this->cube.setPosition(this->position);
	this->cube.setRotation((180.0f / (float)M_PI) *atan2f(this->velocity.y, this->velocity.x));

	this->gravityLine.setPosition(this->position);
	this->dragForceLine.setPosition(this->position);
	this->dragForceLine.setOrigin(sf::Vector2f(this->radius, this->radius));
	this->gravityLine.setOrigin(sf::Vector2f(this->radius, this->radius));
	this->dragForceLine.setFillColor(sf::Color::Blue);
	this->gravityLine.setFillColor(sf::Color::Yellow);
}

Cube::~Cube()
{

}

float Cube::DragCoefficient()//https://forum.solidworks.com/thread/67677
{
	return 2.0f;
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
	sf::Vector2f dragForce = this->DragForce(this->DragCoefficient());
	sf::Vector2f forceVector = dragForce + this->gravity;
	this->dataText.setString("Drag force: " + std::to_string((int)round(sqrt(pow(dragForce.x, 2) + pow(dragForce.y, 2)))) +
		"\nCD: " + std::to_string(this->DragCoefficient()) +
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
	this->cube.setRotation((180.0f / (float)M_PI) *atan2f(this->velocity.y, this->velocity.x));
	updateLines();
	return newPos;
}

sf::FloatRect Cube::getBoundingBox()
{
	return this->cube.getGlobalBounds();
}

