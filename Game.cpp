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
	player.load_bulletInfo_from_file();

	float dt{ 0.f };

	sf::Vector2i mouseGlobalPos;

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

		mouseGlobalPos = sf::Vector2i(sf::Mouse::getPosition(window).x+static_cast<int>(camera.get_posX())-SCREEN_WIDTH/2, sf::Mouse::getPosition(window).y);


		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && player.is_shoot_ok())
		{
			player.gun.emplace_back(&map, mouseGlobalPos, player.get_postion(), &player.bulletInfo); player.reset_lastShotTime();
		}

		dt = clock.restart().asSeconds();

		player.update(dt);

		window.clear();
		camera.update(window);
		map.draw(window,camera.get_posX());
		player.draw(window);

		for (int i = 0; i < static_cast<int>(player.gun.size()); i++)
		{
			player.gun[i].update(dt);
			player.gun[i].draw(window);
			if (player.gun[i].is_to_destroy())
				player.gun.erase(player.gun.begin() + i);
		}

		window.display();
	}

	return 0;
}

Game::~Game()
{
}
