#include <SFML\Graphics.hpp>
#include "GameManager.h"
#include "GameTime.h"
#include "Locator.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1440, 900), "Artelleri");
	window.setVerticalSyncEnabled(true);

	IGameTime* gameTime = new GameTime;
	Locator::provide(gameTime);

	Locator::getGameTime()->StartTimer();

	srand(time(NULL));

	GameManager gm;

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
		window.clear(sf::Color(255, 0, 255));
		window.draw(gm);
		window.display();
	}

	delete gameTime;
	gm.clenup();

	return 0;
}