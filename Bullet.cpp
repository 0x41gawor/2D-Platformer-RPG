#include "Bullet.h"



Bullet::Bullet(Map* map, sf::Vector2i pointPos, sf::Vector2f playerPos,BulletInfo* info)
	:map{map},info{info}
{
	body.setFillColor(info->color);
	body.setPosition(playerPos);
	body.setRadius(info->radius);
	body.setPointCount(10);
	body.setOrigin(sf::Vector2f(body.getGlobalBounds().width / 2, body.getGlobalBounds().height / 2));

	float a = (abs(playerPos.y - pointPos.y)) / (abs(pointPos.x - playerPos.x));
	float angle = atan(a); 

	velocityX = info->velocity * cos(angle);
	velocityY = info->velocity * sin(angle);

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

void Bullet::update(float dt)
{
	posX += velocityX * dt;
	posY += velocityY * dt;
	body.move(velocityX*dt, velocityY*dt);
}

void Bullet::draw(sf::RenderWindow& window)
{
	window.draw(body);
}

bool Bullet::is_to_destroy()
{
	if (map->is_terrain(posX, posY))
		return true;

	return(posX < 0 || posY < 0 || posX>MAP_SIZE_X * GRID || posY > MAP_SIZE_Y * GRID);
}

sf::Vector2f Bullet::get_position()
{
	return sf::Vector2f(posX, posY);
}


Bullet::~Bullet()
{
	map = nullptr;
}
