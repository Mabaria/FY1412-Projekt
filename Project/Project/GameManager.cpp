#include "GameManager.h"
#include "InputHandler.h"
#include "Locator.h"



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

	this->ground.setFillColor(sf::Color::Blue);
	this->ground.setPosition(0, 850);
	this->ground.setSize(sf::Vector2f(1440, 50.0f));
}

GameManager::~GameManager()
{
}

void GameManager::update()
{
}

void GameManager::clenup()
{
	delete this->input;
}
