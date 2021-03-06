#include "Tank.h"
#include "Locator.h"



void Tank::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->dataText);
	target.draw(this->cannon);
	target.draw(this->body);
	for (int i = 0; i < 4; i++) {
		target.draw(wheels[i]);
	}
}

Tank::Tank(sf::Vector2f pos, sf::Color color, bool facingRight)
{
	// Text for displaying the relevant data for the shot
	this->dataFont.loadFromFile("Resources\\Fonts\\arial.ttf");
	this->dataText.setFont(this->dataFont);
	this->dataText.setCharacterSize(12);
	//this->dataText.setColor(sf::Color::White);

	// Body general settings
	this->body.setFillColor(color);
	this->body.setPosition(pos);
	this->body.setSize(sf::Vector2f(25.0f, 12.0f));
	this->bBox.left = this->body.getPosition().x;
	this->bBox.top = this->body.getPosition().y;
	this->bBox.width = this->body.getSize().x;
	this->bBox.height = this->body.getSize().y;

	// Cannon general settings
	this->cannon.setFillColor(sf::Color::Black);
	this->cannon.setSize(sf::Vector2f(24.0f, 8.0f));
	// Cannon orientation settings depending on what way it is facing
	if (facingRight) {
		this->facingRight = true;
		this->cannon.setPosition(pos.x + 5.0f, pos.y - 1.0f);
		this->cannon.setOrigin(2.0f, 2.0f);
		this->cannon.setRotation(-45);
		// Set the text to show the correct initial rotation
		this->dataText.setString("Degrees: " + std::to_string(-(this->cannon.getRotation() - 360)));
		// Text upper left corner
		this->dataText.setPosition(sf::Vector2f(0.0f, 0.0f));
	}
	else {
		this->facingRight = false;
		this->cannon.setPosition(pos.x + 20.0f, pos.y - 1.0f);
		this->cannon.setOrigin(22.0f, 2.0f);
		this->cannon.setRotation(45);
		// Set the text to show the correct initial rotation
		this->dataText.setString("Degrees: " + std::to_string(this->cannon.getRotation()));
		// Text upper right corner
		this->dataText.setOrigin(sf::Vector2f(this->dataText.getGlobalBounds().left + this->dataText.getGlobalBounds().width, 0.0f));
		this->dataText.setPosition(sf::Vector2f(1440.0f, 0.0f));
	}

	// Wheels!
	for (int i = 0; i < 4; i++) {
		wheels[i].setFillColor(sf::Color::Black);
		wheels[i].setRadius(4.0f);
		wheels[i].setPosition(pos.x + (7.0f * i) - 2.0f, pos.y + 6.0f);
	}

	this->selectedProj = ROUNDLEFTSPIN;
	this->myTurn = true;
}


Tank::~Tank()
{
}

void Tank::rotateCannon(float angle)
{
	float dt = Locator::getGameTime()->getDeltaTime();

	if (this->facingRight) {
		if (this->cannon.getRotation() + (angle * dt) > 0.0f && this->cannon.getRotation() < 1.0f) {
			this->cannon.setRotation(0.0f);
		}
		else if (this->cannon.getRotation() + (angle * dt) < 270.0f && this->cannon.getRotation() > 1.0f) {
			this->cannon.setRotation(270.0f);
		}
		else {
			this->cannon.rotate(angle * dt);
		}
	}
	else {
		if (this->cannon.getRotation() + (angle * dt) < 0.0f) {
			this->cannon.setRotation(0.0f);
		}
		else if (this->cannon.getRotation() + (angle * dt) > 90.0f) {
			this->cannon.setRotation(90.0f);
		}
		else {
			this->cannon.rotate(angle * dt);
		}
	}
	
	if(this->facingRight)
		this->dataText.setString("Degrees: " + std::to_string(-(this->cannon.getRotation() - 360)));
	else
		this->dataText.setString("Degrees: " + std::to_string(this->cannon.getRotation()));
}

bool Tank::collision(sf::FloatRect &projBounds)
{
	bool hit = false;

	if (this->bBox.intersects(projBounds)) {
		hit = true;
	}

	return hit;
}

void Tank::shootProjectile(sf::Vector2f &gravity, sf::Vector2f &windSpeed, float airDensity, float airViscosity, Projectile* &activeProjectile)
{
	if (myTurn) {
		if (activeProjectile == nullptr) {
			sf::Vector2f direction;
			if (this->facingRight)
				direction = sf::Vector2f(cos(this->cannon.getRotation()*3.14159265358f / 180.0f), sin(this->cannon.getRotation()*3.14159265358f / 180.0f));
			else
				direction = sf::Vector2f(-cos(this->cannon.getRotation()*3.14159265358f / 180.0f), -sin(this->cannon.getRotation()*3.14159265358f / 180.0f));

			if (this->selectedProj == ROUNDLEFTSPIN)
				activeProjectile = new RoundProjectile(airDensity, airViscosity, this->cannon.getPosition(), gravity, direction, ROUNDSPINLEFT, windSpeed);
			else if (this->selectedProj == ROUNDRIGHTSPIN)
				activeProjectile = new RoundProjectile(airDensity, airViscosity, this->cannon.getPosition(), gravity, direction, ROUNDSPINRIGHT, windSpeed);
			else if (this->selectedProj == ARTILLERYSHELL)
				activeProjectile = new ArtilleryShell(airDensity, airViscosity, this->cannon.getPosition(), gravity, direction, windSpeed);
			else if (this->selectedProj == CUBE)
				activeProjectile = new Cube(airDensity, airViscosity, this->cannon.getPosition(), gravity, direction, windSpeed);
		}
	}
}

PROJECTILETYPE Tank::getSelectedProjectile()
{
	return this->selectedProj;
}

void Tank::setTurn(bool turnState)
{
	this->myTurn = turnState;
}

void Tank::changeProjectile()
{
	this->selectedProj = (PROJECTILETYPE)((this->selectedProj + 1) % TOTALPROJTYPES); // Cycles through projectile types
}
