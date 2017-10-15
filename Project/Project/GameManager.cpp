#include "GameManager.h"
#include "InputHandler.h"
#include "Locator.h"
#include "RotateAimLeftCommand.h"
#include "RotateAimRightCommand.h"
#include "ShootProjectileCommand.h"
#include "ChangeProjectileCommand.h"
#include <iostream>



void GameManager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->ground);
	target.draw(player1);
	target.draw(this->player2);
	if (this->activeProjectile != nullptr) {
		target.draw(*this->activeProjectile);
	}

	if (this->gameOver) {
		target.draw(this->cover);
		target.draw(this->endText);
	}
}

void GameManager::collisionDetection()
{

}

GameManager::GameManager(sf::Vector2f &gravity,sf::Vector2f &windSpeed, float airDensity, float airViscosity) : 
						 player1(sf::Vector2f(75.0f, 838.0f), sf::Color::Green, true),  
						 player2(sf::Vector2f(1325.0f, 838.0f), sf::Color::Red, false)
{
	this->gravity = gravity;
	this->airDensity = airDensity;
	this->airViscosity = airViscosity;
	this->windSpeed = windSpeed;

	this->turn = GREEN;
	this->gameOver = false;

	this->cover.setPosition(0.0f, 0.0f);
	this->cover.setSize(sf::Vector2f(1600, 900));
	this->cover.setFillColor(sf::Color::Black);

	this->font.loadFromFile("Resources\\Fonts\\arial.ttf");

	this->endText.setFont(this->font);
	this->endText.setString("Game Over");
	this->endText.setOrigin(this->endText.getGlobalBounds().left + this->endText.getGlobalBounds().width / 2, this->endText.getGlobalBounds().top + this->endText.getGlobalBounds().height / 2);
	this->endText.setPosition(sf::Vector2f(1440 / 2, 900 / 2));

	this->input = new InputHandler;
	Locator::provide(input);

	this->activeProjectile = nullptr;

	this->player1RotateAimLeft = new RotateAimLeftCommand(&this->player1);
	this->player1RotateAimRight = new RotateAimRightCommand(&this->player1);
	this->player1ChangeProjectile = new ChangeProjectileCommand(&this->player1);
	this->player1ShootProjectile = new ShootProjectileCommand(&this->player1, this->gravity, this->windSpeed, this->airDensity, this->airViscosity, &this->activeProjectile);

	this->player2RotateAimLeft = new RotateAimLeftCommand(&this->player2);
	this->player2RotateAimRight = new RotateAimRightCommand(&this->player2);
	this->player2ShootProjectile = new ShootProjectileCommand(&this->player2, this->gravity, this->windSpeed, this->airDensity, this->airViscosity, &this->activeProjectile);
	this->player2ChangeProjectile = new ChangeProjectileCommand(&this->player2);

	this->input->setCommand(A, this->player1RotateAimLeft);
	this->input->setCommand(D, this->player1RotateAimRight);
	this->input->setCommand(SPACE, this->player1ShootProjectile);
	this->input->setCommand(E, this->player1ChangeProjectile);

	this->input->setCommand(LEFT, this->player2RotateAimLeft);
	this->input->setCommand(RIGHT, this->player2RotateAimRight);
	this->input->setCommand(ENTER, this->player2ShootProjectile);
	this->input->setCommand(RCTRL, this->player2ChangeProjectile);



	this->ground.setFillColor(sf::Color(1,142,14));
	this->ground.setPosition(0, 850);
	this->ground.setSize(sf::Vector2f(1440, 50.0f));
}

GameManager::~GameManager()
{
}

void GameManager::update()
{
	this->input->handleKeys();
	if (this->activeProjectile != nullptr) {
		this->activeProjectile->update();
		if (this->activeProjectile->getPosition().y > 850) {
			delete this->activeProjectile;
			this->activeProjectile = nullptr;
			
			if (this->turn == GREEN) {
				this->turn = RED;
			}
			else {
				this->turn = GREEN;
			}
		}
		else if (this->turn == GREEN && this->player2.collision(this->activeProjectile->getPosition())) {
			this->gameOver = true;
			delete this->activeProjectile;
			this->activeProjectile = nullptr;
		}
		else if (this->turn == RED && this->player1.collision(this->activeProjectile->getPosition())) {
			this->gameOver = true;
			delete this->activeProjectile;
			this->activeProjectile = nullptr;
		}
	}
	if (this->gameOver) {
		int test = 0;
	}
}

void GameManager::cleanup()
{
	delete this->input;
	delete this->player1RotateAimLeft;
	delete this->player1RotateAimRight;
	delete this->player2RotateAimLeft;
	delete this->player2RotateAimRight;
}
