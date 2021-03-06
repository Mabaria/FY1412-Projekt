#include "ArtilleryShell.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Locator.h"

#define ARTILLERYPROJMASS 25
#define ARTILLERYPROJVELOCITY 600
#define ARTILLERYPROJRADIUS 0.40f
//#define ROUNDPROJANGLEVELOCITY -0.00f 



ArtilleryShell::ArtilleryShell(float airDensity, float airViscosity, sf::Vector2f position, sf::Vector2f gravity, sf::Vector2f direction, sf::Vector2f windSpeed)
{
	this->mass = ARTILLERYPROJMASS;
	this->radius = ARTILLERYPROJRADIUS;
	this->area = this->radius*this->radius*(float)M_PI;
	this->position = position;
	this->velocity = sf::Vector2f(direction.x*ARTILLERYPROJVELOCITY, direction.y*ARTILLERYPROJVELOCITY);
	this->gravity = sf::Vector2f(gravity.x*ARTILLERYPROJMASS, gravity.y*ARTILLERYPROJMASS);
	this->airDensity = airDensity;
	this->airViscosity = airViscosity;
	this->windSpeed = windSpeed;

	this->dataFont.loadFromFile("Resources\\Fonts\\arial.ttf");
	this->dataText.setFont(this->dataFont);
	this->dataText.setCharacterSize(12);

	this->dataText.setString("Drag force: 0");
	this->dataText.setOrigin(sf::Vector2f(this->dataText.getGlobalBounds().left + this->dataText.getGlobalBounds().width, 0.0f));
	this->dataText.setPosition(sf::Vector2f(1000.0f, 200.0f));

	this->triangle.setPointCount(3);
	this->triangle.setPoint(0, sf::Vector2f(0.f, 0.f));
	this->triangle.setPoint(1, sf::Vector2f(0.f, 10.f));
	this->triangle.setPoint(2, sf::Vector2f(10.f, 5.f));
	this->triangle.setFillColor(sf::Color::Black);
	this->triangle.setOrigin(5.f / 3.f, 2.5f);
	this->triangle.setPosition(this->position);
	//this->directionVec=sf::Vector2f((this->position.x+2,5)-(this->position.x),((this->position.y-2.5)))
	this->triangle.setRotation((180.0f / 3.14159265358f) *atan2f(this->velocity.y,this->velocity.x));


	this->gravityLine.setPosition(this->position);
	this->dragForceLine.setPosition(this->position);

	this->dragForceLine.setFillColor(sf::Color::Blue);
	this->gravityLine.setFillColor(sf::Color::Yellow);


}

ArtilleryShell::~ArtilleryShell() {



}

void ArtilleryShell::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->triangle);
	target.draw(this->dataText);
	target.draw(this->dragForceLine);
	target.draw(this->gravityLine);
}

void ArtilleryShell::updateLines() {

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

float ArtilleryShell::DragCoefficient() //Based on cd/mach graph from http://www.kevinboone.net/zom2.html "The G tables" the second graph
{
	float cd = -1;
	float speed = sqrt(pow(this->velocity.x, 2) + pow(this->velocity.y, 2));
	if (speed < 340)
	{
		cd = 0.12;
	}
	else
	{
		cd = 0.41 - ((0.25 / 4)*(speed/340));
	}

	return cd;
}

sf::Vector2f ArtilleryShell::DragForce(float cd)
{
	sf::Vector2f relativeSpeed = this->velocity - this->windSpeed;
	float speed = sqrt(pow(relativeSpeed.x, 2) + pow(relativeSpeed.y, 2));
	sf::Vector2f dragForce;
	if (speed < 0.5f)
		dragForce = sf::Vector2f(0.0f, 0.0f);
	float force = -0.5f*cd*this->airDensity*this->area*pow(speed, 2);
	dragForce = sf::Vector2f((relativeSpeed.x / speed)*force, (relativeSpeed.y / speed)*force);

	return dragForce;
}

sf::Vector2f ArtilleryShell::TotalAcceleration()
{
	sf::Vector2f dragForce = this->DragForce(this->DragCoefficient());
	sf::Vector2f forceVector = dragForce + this->gravity;
	this->dataText.setString("Drag force: " + std::to_string((int)round(sqrt(pow(dragForce.x, 2) + pow(dragForce.y, 2)))) +
		"\nCD: " + std::to_string(this->DragCoefficient()) +
		"\nVelocity: " + std::to_string(sqrt(pow(this->velocity.x, 2) + pow(this->velocity.y, 2))));

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
	this->triangle.setRotation((180.0f / 3.14159265358f)*(atan2f(this->velocity.y, this->velocity.x)));
	updateLines();
	return newPos;
}

sf::FloatRect ArtilleryShell::getBoundingBox()
{
	return this->triangle.getGlobalBounds();
}
