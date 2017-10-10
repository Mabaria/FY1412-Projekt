#include "GameManager.h"
#include "InputHandler.h"
#include "Locator.h"
#include "RotateAimLeftCommand.h"
#include "RotateAimRightCommand.h"
#include <iostream>



void GameManager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->ground);
	target.draw(player1);
	target.draw(this->player2);
}

GameManager::GameManager() : player1(sf::Vector2f(75.0f, 838.0f), sf::Color::Green, true),
							 player2(sf::Vector2f(1325.0f, 838.0f), sf::Color::Red, false)
{
	this->input = new InputHandler;
	Locator::provide(input);

	this->player1RotateAimLeft = new RotateAimLeftCommand(&this->player1);
	this->player1RotateAimRight = new RotateAimRightCommand(&this->player1);
	this->player2RotateAimLeft = new RotateAimLeftCommand(&this->player2);
	this->player2RotateAimRight = new RotateAimRightCommand(&this->player2);

	this->input->setCommand(A, this->player1RotateAimLeft);
	this->input->setCommand(D, this->player1RotateAimRight);
	this->input->setCommand(LEFT, this->player2RotateAimLeft);
	this->input->setCommand(RIGHT, this->player2RotateAimRight);

	this->ground.setFillColor(sf::Color::Blue);
	this->ground.setPosition(0, 850);
	this->ground.setSize(sf::Vector2f(1440, 50.0f));
}

GameManager::~GameManager()
{
}

void GameManager::update()
{
	this->input->handleKeys();
}

void GameManager::clenup()
{
	delete this->input;
	delete this->player1RotateAimLeft;
	delete this->player1RotateAimRight;
	delete this->player2RotateAimLeft;
	delete this->player2RotateAimRight;
}
