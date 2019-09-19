#include "Game.h"


Game::Game()
{
}

int Game::play()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode::getDesktopMode(), "2D-PLATFORMER-RPG", sf::Style::None);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}

		window.clear();
		map.draw(window);
		window.display();
	}

	return 0;
}

Game::~Game()
{
}
