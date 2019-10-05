#include "healthBar.h"

healthBar::healthBar():maxHealth{ 1000.f },posY {100.f },posX{0.f},width{200},height{40}, percent{1.f}
{
	body.setSize(sf::Vector2f(width, height));
	frame.setSize(sf::Vector2f(width, height));
	body.setOrigin(width/2.f,height/2.f);
	frame.setOrigin(width / 2.f, height / 2.f);

	frame.setOutlineThickness(1);
	frame.setFillColor(sf::Color::Transparent);
	frame.setOutlineColor(sf::Color(255, 255, 255));
}

void healthBar::update(float camPos, float health)
{
	body.setPosition(camPos, posY);
	frame.setPosition(camPos, posY);

	percent = health / maxHealth;

	body.setSize(sf::Vector2f(percent * width, height));

	body.setFillColor(sf::Color((1- percent)*255, percent *255, 0));
}

void healthBar::draw(sf::RenderWindow& window)
{
	window.draw(frame);
	window.draw(body);
}

void healthBar::set_maxHealth(float maxHealth)
{
	this->maxHealth = maxHealth;
}
