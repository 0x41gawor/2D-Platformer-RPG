#include "Bullet.h"



Bullet::Bullet(Map* map, sf::Vector2i pointPos, sf::Vector2f playerPos)
	:map{map},radius{5},color{sf::Color(255,255,255)},damage{0.f},velocity{3.f},attackSpeed{0.2f}
{
	body.setFillColor(color);
	body.setPosition(playerPos);
	body.setRadius(radius);
	body.setPointCount(10);
	body.setOrigin(sf::Vector2f(body.getGlobalBounds().width / 2, body.getGlobalBounds().height / 2));

	float a = (abs(playerPos.y - pointPos.y)) / (abs(pointPos.x - playerPos.x));
	float angle = atan(a); 

	velocityX = velocity * cos(angle);
	velocityY = velocity * sin(angle);

	posX = playerPos.x;
	posY = playerPos.y;

	if (pointPos.x <= playerPos.x)
	{
		velocityX *= -1;
		if (pointPos.y < playerPos.y)
			velocityY *= -1;
	}
	else
	{
		if (pointPos.y < playerPos.y)
			velocityY *= -1;
	}
}

void Bullet::update()
{
	posX += velocityX;
	posY += velocityY;
	body.move(velocityX, velocityY);
}

void Bullet::draw(sf::RenderWindow& window)
{
	window.draw(body);
}

sf::Vector2f Bullet::get_position()
{
	return sf::Vector2f(posX, posY);
}

bool Bullet::is_to_destroy()
{
	if (map->is_terrain(posX, posY))
		return true;

	return(posX < 0 || posY < 0 || posX>MAP_SIZE_X * GRID || posY > MAP_SIZE_Y * GRID);
}

float Bullet::get_damage()
{
	return damage;
}

void Bullet::set_damage(float dam)
{
	damage = dam;
}

void Bullet::set_velocity(float vel)
{
	velocity = vel;
}

void Bullet::set_attackSpeed(float ats)
{
	attackSpeed = ats;
}

void Bullet::set_radius(int rad)
{
	radius = rad;
}

void Bullet::set_color(sf::Color col)
{
	color = col;
}

Bullet::~Bullet()
{
	map = nullptr;
}
