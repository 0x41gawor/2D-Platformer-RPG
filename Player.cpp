#include "Player.h"

static const float g = 6.f;


Player::Player(Map* map, sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
	:map{map},movementSpeed{300.f},mass{25.f},velocityY{0.f},jumpForce{35.f},onGround{false},width{50.f},height{80.f},leftBanned{false},
	rightBanned{ false },animation{ texture, imageCount, switchTime },texRow{ 0 },faceRigt{ true },lastShotTime{0.f},health{1000.f},ATK{1.f}
{
	body.setSize(sf::Vector2f(width,height));
	body.setTexture(texture);
	body.setOrigin(width/2, height/2);
	body.setPosition(200, 2 * GRID + height / 2);
}

void Player::update(const float& dt)
{
	lastShotTime += dt;

	movement.x = 0.f;
	movement.y = 0.f;

	onGround = (map->is_terrain(pos.x - 25.f, pos.y + 40.f) || map->is_terrain(pos.x + 25.f, pos.y + 40.f)) ? true : false;

	texRow = onGround ? 0 : ((velocityY < 0) ? 2 : 3);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !leftBanned) 
	{
		movement.x = -movementSpeed * dt;
		if (onGround) texRow = 1;
		faceRigt = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !rightBanned) 
	{
		movement.x = movementSpeed * dt;
		if (onGround) texRow = 1;
		faceRigt = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && onGround) 
		apply_force(jumpForce);										  

	velocityY += onGround ? 0 : g; 

	if (!onGround) 
		movement.y= velocityY * dt;  

	animation.update(texRow, dt, faceRigt);
	body.setTextureRect(animation.uvRect);

	body.move(movement);

	collision();
}

void Player::draw(sf::RenderWindow& w)
{
	w.draw(body);
}

void Player::apply_force(float force)
{
	velocityY = -force * 1000 / mass; 
	onGround = false;
}

void Player::collision()
{
	pos = body.getPosition();

	if (onGround)
		pos.y = static_cast<float>(static_cast<int>((pos.y + 40.f) / GRID) * GRID - height / 2.f);

	if ((map->is_terrain(pos.x - 25.f, pos.y - 40.f) || map->is_terrain(pos.x + 25.f, pos.y - 40.f)) && velocityY < 0)
	{
		velocityY = 0;
	}

	leftBanned = (map->is_terrain(pos.x - 27.f, pos.y - 30.f) || map->is_terrain(pos.x - 27.f, pos.y + 30.f)) ? true : false;
	rightBanned = (map->is_terrain(pos.x + 27.f, pos.y - 30.f) || map->is_terrain(pos.x + 27.f, pos.y + 30.f)) ? true : false;

	if (pos.x < 0)
		pos.x = 0;
	else if (pos.x > MAP_SIZE_X * GRID)
		pos.x =0;

	if (pos.y > MAP_SIZE_Y * GRID)
		pos.y = 0;

	body.setPosition(pos);
}

bool Player::is_shoot_ok()
{
	return lastShotTime>bulletInfo.attackSpeed;
}

void Player::reset_lastShotTime()
{
	lastShotTime = 0.f;
}

void Player::load_from_file(std::string username)
{
	std::string line{ "" };

	std::ifstream file;
	std::string filename{ "users/" + username + ".txt" };

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


	file.open(weaponFilename);
	int weaponValues[8] = { 0 };
	i = 0;
	while (!file.eof())
	{
		getline(file, line);
		if (i < 8)
			weaponValues[i] = atoi(line.c_str());
		i++;
	}
	file.close();

	file.open(shoeFilename);
	int shoeValues[3] = { 0 };
	i = 0;
	while (!file.eof())
	{
		getline(file, line);
		if (i < 3)
			shoeValues[i] = atoi(line.c_str());
		i++;
	}
	file.close();

	file.open(kevlarFilename);
	int kevlarValues[2] = { 0 };
	i = 0;
	while (!file.eof())
	{
		getline(file, line);
		if (i < 2)
			kevlarValues[i] = atoi(line.c_str());
		i++;
	}
	file.close();

	health				   = static_cast<float>(userValues[6 - 4] + userValues[8 - 4] * 10 + kevlarValues[0]);
	movementSpeed		   = static_cast<float>(userValues[4 - 4] + shoeValues[0]);
	jumpForce			   = static_cast<float>(userValues[5 - 4] + shoeValues[1]);
	mass				   = static_cast<float>(15.f + weaponValues[7] + shoeValues[2] + kevlarValues[1]);
	bulletInfo.damage	   = static_cast<float>(weaponValues[0]);
	bulletInfo.attackSpeed = static_cast<float>(weaponValues[1]) / 10.f;
	bulletInfo.velocity	   = static_cast<float>(weaponValues[2]);
	bulletInfo.radius	   = static_cast<float>(weaponValues[3]);
	bulletInfo.color	   = sf::Color(sf::Uint8(weaponValues[4]), sf::Uint8(weaponValues[5]), sf::Uint8(weaponValues[6]));
}

void Player::take_damage(float dmg)
{
		health -= dmg;
}

sf::Vector2f Player::get_position()
{
	return body.getPosition();
}

float Player::get_bullet_damage()
{
	return bulletInfo.damage * ATK;
}

float Player::get_health()
{
	return health;
}

void Player::print_info()
{
	std::cout << "MS: " << movementSpeed << std::endl;
	std::cout << "jumpForce: " << jumpForce << std::endl;
	std::cout << "health: " << health << std::endl;
	std::cout << "ATK: " <<ATK<<std::endl;
	std::cout << "mass: " << mass << std::endl;
	std::cout << "damage: " << bulletInfo.damage << std::endl;
	std::cout << "AS: " << bulletInfo.attackSpeed << std::endl;
	std::cout << "radius: " << bulletInfo.radius << std::endl;
	std::cout << "speed: " << bulletInfo.velocity << std::endl;
	
	system("pause");
}

Player::~Player()
{
	map = nullptr;
}
