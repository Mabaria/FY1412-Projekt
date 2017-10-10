#include "Tank.h"
#include "Locator.h"



void Tank::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->cannon);
	target.draw(this->body);
	for (int i = 0; i < 4; i++) {
		target.draw(wheels[i]);
	}
}

Tank::Tank(sf::Vector2f pos, sf::Color color, bool facingRight)
{
	// Body general settings
	this->body.setFillColor(color);
	this->body.setPosition(pos);
	this->body.setSize(sf::Vector2f(25.0f, 12.0f));

	// Cannon general settings
	this->cannon.setFillColor(sf::Color::Black);
	this->cannon.setSize(sf::Vector2f(24.0f, 8.0f));
	// Cannon orientation settings depending on what way it is facing
	if (facingRight) {
		this->cannon.setPosition(pos.x + 5.0f, pos.y - 1.0f);
		this->cannon.setOrigin(2.0f, 2.0f);
		this->cannon.setRotation(-45);
	}
	else {
		this->cannon.setPosition(pos.x + 20.0f, pos.y - 1.0f);
		this->cannon.setOrigin(22.0f, 2.0f);
		this->cannon.setRotation(45);
	}

	// Wheels!
	for (int i = 0; i < 4; i++) {
		wheels[i].setFillColor(sf::Color::Black);
		wheels[i].setRadius(4.0f);
		wheels[i].setPosition(pos.x + (7.0f * i) - 2.0f, pos.y + 6.0f);
	}
}


Tank::~Tank()
{
}

void Tank::rotateCannon(float angle)
{
	float dt = Locator::getGameTime()->getDeltaTime();

	this->cannon.rotate(angle * dt);
}
