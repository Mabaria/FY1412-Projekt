#include "GameManager.h"
#include "InputHandler.h"
#include "Locator.h"



void GameManager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->ground);
	target.draw(this->player1Tank);
	target.draw(this->player2Tank);
}

GameManager::GameManager()
{
	this->input = new InputHandler;
	Locator::provide(input);

	this->ground.setFillColor(sf::Color::Blue);
	this->ground.setPosition(0, 550);
	this->ground.setSize(sf::Vector2f(800.0f, 50.0f));

	this->player1Tank.setFillColor(sf::Color::Green);
	this->player1Tank.setPosition(50, 538);
	this->player1Tank.setSize(sf::Vector2f(25.0f, 12.0f));

	this->player2Tank.setFillColor(sf::Color::Red);
	this->player2Tank.setPosition(725, 538);
	this->player2Tank.setSize(sf::Vector2f(25.0f, 12.0f));
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
