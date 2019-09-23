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

	map.load_from_file(setup_player("user"));

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
		cursor.setPosition(static_cast<sf::Vector2f>(mouseGlobalPos));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && player.is_shoot_ok())
		{
			player.gun.emplace_back(&map, mouseGlobalPos, player.get_position(), &player.bulletInfo); player.reset_lastShotTime();
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
		window.draw(cursor);
		window.display();
	}
	player.print_info();

	return 0;
}

std::string Game::setup_player(std::string username)
{
	std::string line{ "" };

	std::ifstream file;
	std::string filename = "users/" + username + ".txt";

	std::string files[4];
	int userValues[6] = { 0 };

	file.open(filename);
	int i = 0;
	while (!file.eof())
	{
		getline(file, line);
		if (i <= 3)
			files[i] = line;
		else if (i > 3 && i < 10)
			userValues[i - 4] = atoi(line.c_str());
		i++;
	}
	file.close();

	std::string levelFilename  = "levels/" + files[0];
	std::string weaponFilename = "store/"  + files[1] + ".txt";
	std::string shoeFilename   = "store/"  + files[2] + ".txt";
	std::string kevlarFilename = "store/"  + files[3] + ".txt";

	std::ifstream weaponFile;
	std::ifstream shoeFile;
	std::ifstream kevlarFile;
	
	weaponFile.open(weaponFilename);
	int weaponValues[8] = { 0 };
	i = 0;
	while (!weaponFile.eof())
	{
		getline(weaponFile, line);
		if (i < 8)
			weaponValues[i] = atoi(line.c_str());
		i++;
	}
	weaponFile.close();
	
	shoeFile.open(shoeFilename);
	int shoeValues[3] = { 0 };
	i = 0;
	while (!shoeFile.eof())
	{
		getline(shoeFile, line);
		if (i < 3)
			shoeValues[i] = atoi(line.c_str());
		i++;
	}
	shoeFile.close();
	
	kevlarFile.open(kevlarFilename);
	int kevlarValues[2] = { 0 };
	i = 0;
	while (!kevlarFile.eof())
	{
		getline(kevlarFile, line);
		if (i < 2)
			kevlarValues[i] = atoi(line.c_str());
		i++;
	}
	kevlarFile.close();

	player.set_health(static_cast<float>(userValues[6-4]+userValues[8 - 4]*10+kevlarValues[0]));
	player.set_movementSpeed(static_cast<float>(userValues[4 - 4] + shoeValues[0]));
	player.set_jumpForce(static_cast<float>(userValues[5 - 4] + shoeValues[1]));
	player.set_mass(static_cast<float>(15.f + weaponValues[7] + shoeValues[2] + kevlarValues[1]));
	player.set_bulletInfo_damage(static_cast<float>(weaponValues[0]));
	player.set_bulletInfo_attackSpeed(static_cast<float>(weaponValues[1])/10.f);
	player.set_bulletInfo_velocity(static_cast<float>(weaponValues[2]));
	player.set_bulletInfo_radius(static_cast<float>(weaponValues[3]));
	player.set_bulletInfo_color(sf::Color(sf::Uint8(weaponValues[4]), sf::Uint8(weaponValues[5]), sf::Uint8(weaponValues[6])));

	return levelFilename;
}

Game::~Game()
{
}
