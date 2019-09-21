#include "Game.h"


Game::Game(Textures* textures)
	:textures{*textures},player {&map, & textures->player}
{
}


int Game::play()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode::getDesktopMode(), "2D-PLATFORMER-RPG", sf::Style::None);

	map.load_from_file();

	float dt{ 0.f };

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
		map.draw(window,camera.get_posX());
		player.draw(window);
		window.display();
	}

	return 0;
}

Game::~Game()
{
}
