#include <SFML\Graphics.hpp>
#include "GameManager.h"
#include "GameTime.h"
#include "Locator.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Artelleri");
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
			//----Closes window if windows is closed manually or getExit returns true----
			if (event.type == sf::Event::Closed)
				window.close();
		}

		gm.update();
		window.clear();
		window.draw(gm);
		window.display();
	}

	delete gameTime;

	return 0;
}