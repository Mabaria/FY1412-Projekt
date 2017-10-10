#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML\Graphics.hpp>

class GameManager : public sf::Drawable
{
private:
	void GameManager::draw(sf::RenderTarget & target, sf::RenderStates states) const;
	
public:
	GameManager();
	~GameManager();

	void update();
};

#endif
