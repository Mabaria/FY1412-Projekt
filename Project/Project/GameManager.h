#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML\Graphics.hpp>
#include "IInputHandler.h"
#include "Tank.h"
#include "Projectile.h"

class GameManager : public sf::Drawable
{
private:
	IInputHandler* input;
	sf::RectangleShape ground;

	Tank player1;
	Tank player2;

	Projectile* activeProjectile;

	Command* player1RotateAimLeft;
	Command* player1RotateAimRight;
	Command* player1ShootProjectile;
	Command* player1ChangeProjectile;

	Command* player2RotateAimLeft;
	Command* player2RotateAimRight;
	Command* player2ShootProjectile;
	Command* player2ChangeProjectile;

	sf::Vector2f gravity;
	float airDensity;
	float airViscosity;

	void GameManager::draw(sf::RenderTarget & target, sf::RenderStates states) const;
	
public:
	GameManager(sf::Vector2f &gravity = sf::Vector2f(0.0f, 9.82f), float airDensity = 1.22f, float airViscosity = 1.1827f);
	~GameManager();

	void update();
	void cleanup();
};

#endif
