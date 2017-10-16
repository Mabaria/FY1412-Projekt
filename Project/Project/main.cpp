#include <SFML\Graphics.hpp>
#include "GameManager.h"
#include "GameTime.h"
#include "Locator.h"

#define WINDX 5.0f
#define WINDY 0.0f
#define GRAVITYX 0.0f
#define GRAVITYY 9.82f
#define AIRDENSITY 1.22f
#define AIRVISCOSITY 0.00001827f




int main()
{
	sf::RenderWindow window(sf::VideoMode(1440, 900), "Artilleri");
	window.setVerticalSyncEnabled(true);

	IGameTime* gameTime = new GameTime;
	Locator::provide(gameTime);

	Locator::getGameTime()->StartTimer();

	srand(time(NULL));

	GameManager gm(sf::Vector2f(GRAVITYX, GRAVITYY), sf::Vector2f(WINDX, WINDY), AIRDENSITY, AIRVISCOSITY);

	while (window.isOpen())
	{
		Locator::getGameTime()->UpdateFrameTime();

		sf::Event event;
		while (window.pollEvent(event))
		{
			// Closes window if windows is closed manually
			if (event.type == sf::Event::Closed)
				window.close();
		}

		gm.update();
		window.clear(sf::Color(135, 206, 250));
		window.draw(gm);
		window.display();
	}

	delete gameTime;
	gm.cleanup();

	return 0;
}