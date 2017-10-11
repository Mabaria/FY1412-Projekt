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

	sf::Vector2f gravity;
	float airDensity;
	float airViscosity;

	void GameManager::draw(sf::RenderTarget & target, sf::RenderStates states) const;
	
public:
	GameManager(sf::Vector2f &gravity = sf::Vector2f(0.0f, 9.82f), float airDensity = 1.22f, float airViscosity = 0.00001827f);
	~GameManager();

	void update();
	void cleanup();
};

#endif
