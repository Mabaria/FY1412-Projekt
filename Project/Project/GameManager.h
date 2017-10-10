#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML\Graphics.hpp>
#include "IInputHandler.h"

class GameManager : public sf::Drawable
{
private:
	IInputHandler* input;
	sf::RectangleShape ground;
	sf::RectangleShape player1Tank;
	sf::RectangleShape player2Tank;

	void GameManager::draw(sf::RenderTarget & target, sf::RenderStates states) const;
	
public:
	GameManager();
	~GameManager();

	void update();
	void clenup();
};

#endif
