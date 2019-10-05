#pragma once
#include <SFML/Graphics.hpp>

class healthBar
{
  private:
																						 //D R A W
	sf::RectangleShape frame;															 //frame around health bar to point max health
	sf::RectangleShape body;															 //actual health representation
	float posY;																			 //position of health bar
	float posX;																			 //.|.
	float width;																		 //size of health bar
	float height;																		 //.|.

																						 //U P D A T E
	float maxHealth;																	 //max health to calculate procent
	float percent;																		 //what percentage of your maximum health is current

  public:

	healthBar();

	void update(float camPos, float health);											 //update [change pos, size and color]
	void draw(sf::RenderWindow& window);												 //draw		

	void set_maxHealth(float maxHealth);												 //sets maxHealth

};

