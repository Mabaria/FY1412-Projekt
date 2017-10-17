#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML\Graphics.hpp>
#include "IInputHandler.h"
#include "Tank.h"
#include "Projectile.h"

enum TURN { GREEN, RED };

class GameManager : public sf::Drawable
{
private:
	IInputHandler* input;
	sf::RectangleShape ground;
	sf::ConvexShape hill;

	Tank player1;
	Tank player2;
	TURN turn;
	bool gameOver;
	sf::RectangleShape cover;
	sf::Text endText;
	sf::Font font;
	sf::Text selectedProjectileText;
	sf::Text windText;

	Projectile* activeProjectile;

	Command* player1RotateAimLeft;
	Command* player1RotateAimRight;
	Command* player1ShootProjectile;
	// Command* player1ChangeProjectile;

	Command* player2RotateAimLeft;
	Command* player2RotateAimRight;
	Command* player2ShootProjectile;
	// Command* player2ChangeProjectile;

	Command* playersChangeProjectile;

	sf::Vector2f gravity;
	sf::Vector2f windSpeed;
	float airDensity;
	float airViscosity;

	void GameManager::draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void collisionDetection();
	
public:
	GameManager(sf::Vector2f &gravity = sf::Vector2f(0.0f, 9.82f), sf::Vector2f &windSpeed = sf::Vector2f(50.0f, -0.0f), float airDensity = 1.22f, float airViscosity = 0.00001827f);
	~GameManager();

	void update();
	void cleanup();
};

#endif
