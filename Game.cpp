#include "Game.h"


Game::Game():player{&map}
{
}

int Game::play()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode::getDesktopMode(), "2D-PLATFORMER-RPG", sf::Style::None);

	float dt;

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

		dt = clock.restart().asSeconds();

		player.update(dt);

		window.clear();
		camera.update(window);
		map.draw(window);
		player.draw(window);
		window.display();
	}

	return 0;
}

Game::~Game()
{
}
