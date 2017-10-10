#pragma once
#ifndef TANK_H
#define TANK_H

#include <SFML\Graphics.hpp>

class Tank : public sf::Drawable
{
private:
	sf::RectangleShape body;
	sf::RectangleShape cannon;
	sf::CircleShape wheels[4];

	void draw(sf::RenderTarget & target, sf::RenderStates states) const;

public:
	Tank(sf::Vector2f pos, sf::Color color, bool facingRight);
	~Tank();

	void rotateCannon(float angle);
};

#endif
