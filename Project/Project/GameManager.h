#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML\Graphics.hpp>
#include "IInputHandler.h"
#include "Tank.h"

class GameManager : public sf::Drawable
{
private:
	IInputHandler* input;
	sf::RectangleShape ground;

	Tank player1;
	Tank player2;

	Command* player1RotateAimLeft;
	Command* player1RotateAimRight;
	Command* player2RotateAimLeft;
	Command* player2RotateAimRight;

	void GameManager::draw(sf::RenderTarget & target, sf::RenderStates states) const;
	
public:
	GameManager();
	~GameManager();

	void update();
	void cleanup();
};

#endif
