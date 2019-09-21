#include "Player.h"

static const float g = 5.f;


Player::Player(Map* map, sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
	:map{map},movementSpeed{400.f},mass{20.f},velocityY{0.f},jumpForce{30.f},onGround{false},width{50.f},height{80.f},leftBanned{false},
	rightBanned{ false }, animation{ texture, imageCount, switchTime }, texRow{ 0 }, faceRigt{ true }
{
	body.setSize(sf::Vector2f(width,height));
	body.setTexture(texture);
	body.setOrigin(width/2, height/2);
	body.setPosition(200, 2 * GRID + height / 2);

	a = 40.f;
	b = 30.f;
	c = 27.f;
	d = 25.f;
}

void Player::update(const float& dt)
{
	lastPos = body.getPosition();	//last frame postion

	onGround = (map->is_terrain(lastPos.x - d, lastPos.y + a) || map->is_terrain(lastPos.x + d, lastPos.y + a)) ? true : false; //setting onGround value

	texRow = onGround ? 0 : ((velocityY < 0) ? 2 : 3);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !leftBanned) //move left
	{
		body.move(-movementSpeed * dt, 0.f);
		if (onGround) texRow = 1;
		faceRigt = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !rightBanned) //move right
	{
		body.move(movementSpeed * dt, 0.f);
		if (onGround) texRow = 1;
		faceRigt = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && onGround) //if W clicked and  player stands on ground
		apply_force(jumpForce);										  //apply force so he can jump

	velocityY += ((onGround) ? 0 : g); //if onGround is false player falls else his velocityY is equal to 0

	if (!onGround) //if player falls he is moving
		body.move(0.f, velocityY * dt);  //down

	animation.update(texRow, dt, faceRigt);
	body.setTextureRect(animation.uvRect);

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
	sf::Vector2f newPos = body.getPosition();

	if (onGround)
		newPos.y = static_cast<float>(static_cast<int>((newPos.y + 40.f) / GRID) * GRID - height/2.f);

	//up
	if ((map->is_terrain(lastPos.x - d, lastPos.y - a) || map->is_terrain(lastPos.x + d, lastPos.y - a)) && velocityY < 0)
		newPos.y = lastPos.y;

	//sides
	leftBanned = (map->is_terrain(lastPos.x - c, lastPos.y - b) || map->is_terrain(lastPos.x - c, lastPos.y + b)) ? true : false;
	rightBanned = (map->is_terrain(lastPos.x + c, lastPos.y - b) || map->is_terrain(lastPos.x + c, lastPos.y + b)) ? true : false;

	//dont leave map
	if (newPos.x < 0)
		newPos.x = 0;
	else if (newPos.x > MAP_SIZE_X * GRID)
		newPos.x = MAP_SIZE_X * GRID;

	if (newPos.y > MAP_SIZE_Y * GRID)
		newPos.y = 0;

	body.setPosition(newPos);
}

Player::~Player()
{
	map = nullptr;
}
