#include "Game.h"


Game::Game(Textures* textures)
	:textures{*textures},player {&map, & textures->player}
{
	cursor.setTexture(textures->cursor);
	cursor.setOrigin(5.f,5.f);
}

int Game::play()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode::getDesktopMode(), "2D-PLATFORMER-RPG", sf::Style::None);
	window.setMouseCursorVisible(false);

	map.load_from_file("user");
	player.load_from_file("user");
	playerHealthBar.set_maxHealth(player.get_health());

	float dt{ 0.f };

	sf::Vector2i mouseGlobalPos;

	while (window.isOpen())
	{
		//<temporarily here>
		if (player.get_health() >= 0.f)
			player.take_damage(0.2f);
		else
			player.take_damage(-1100);
		//</temporarily here>
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}

		mouseGlobalPos = sf::Vector2i(sf::Mouse::getPosition(window).x+static_cast<int>(camera.get_posX())-SCREEN_WIDTH/2, sf::Mouse::getPosition(window).y);
		cursor.setPosition(static_cast<sf::Vector2f>(mouseGlobalPos));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && player.is_shoot_ok())
		{
			player.gun.emplace_back(&map, mouseGlobalPos, player.get_position(), &player.bulletInfo); player.reset_lastShotTime();
		}

		dt = clock.restart().asSeconds();

		player.update(dt);

		window.clear();
		camera.update(window);
		playerHealthBar.update(camera.get_posX(), player.get_health());
		map.draw(window,camera.get_posX());
		player.draw(window);

		for (int i = 0; i < static_cast<int>(player.gun.size()); i++)
		{
			player.gun[i].update(dt);
			player.gun[i].draw(window);
			if (player.gun[i].is_to_destroy())
				player.gun.erase(player.gun.begin() + i);
		}
		playerHealthBar.draw(window);
		window.draw(cursor);
		window.display();
	}
	player.print_info();

	return 0;
}

Game::~Game()
{
}
