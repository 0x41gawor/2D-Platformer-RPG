#include "Player.h"

static const float g = 6.f;


Player::Player(Map* map, sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
	:map{map},movementSpeed{300.f},mass{25.f},velocityY{0.f},jumpForce{35.f},onGround{false},width{50.f},height{80.f},leftBanned{false},
	rightBanned{ false }, animation{ texture, imageCount, switchTime }, texRow{ 0 }, faceRigt{ true },lastShotTime{0.f},health{1000.f},ATK{1.f}
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

sf::Vector2f Player::get_position()
{
	return body.getPosition();
}

float Player::get_bullet_damage()
{
	return bulletInfo.damage*ATK;
}

void Player::set_movementSpeed(float x)
{
	if (x < 0.f) return;

	movementSpeed = x;

}

void Player::set_mass(float x)
{
	if (x < 0.f) return;
	mass = x;
}

void Player::set_jumpForce(float x)
{
	if (x < 0.f) return;
	jumpForce = x;
}

void Player::set_health(float x)
{
	if (x < 0.f) return;
	health = x;
}

void Player::set_bulletInfo_radius(float x)
{
	bulletInfo.radius = x;
}

void Player::set_bulletInfo_color(sf::Color x)
{
	bulletInfo.color = x;
}

void Player::set_bulletInfo_damage(float x)
{
	bulletInfo.damage = x;
}

void Player::set_bulletInfo_velocity(float x)
{
	bulletInfo.velocity = x;
}

void Player::set_bulletInfo_attackSpeed(float x)
{
	bulletInfo.attackSpeed =x;
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
	getchar();
	getchar();
}

Player::~Player()
{
	map = nullptr;
}
