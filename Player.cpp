#include "Player.h"

static const float g = 6.f;


Player::Player(Map* map, sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
	:map{map},movementSpeed{300.f},mass{25.f},velocityY{0.f},jumpForce{35.f},onGround{false},width{50.f},height{80.f},leftBanned{false},
	rightBanned{ false }, animation{ texture, imageCount, switchTime }, texRow{ 0 }, faceRigt{ true },lastShotTime{0.f}
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

void Player::load_bulletInfo_from_file(std::string filename)
{
	//<temporarily this way>
	bulletInfo.color = sf::Color(255, 255, 255);
	bulletInfo.radius = 5.f;
	bulletInfo.damage = 100.f;
	bulletInfo.velocity = 600.f;
	bulletInfo.attackSpeed = 0.1f;
	//</temporarily this way>
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

Player::~Player()
{
	map = nullptr;
}
