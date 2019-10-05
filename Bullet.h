#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

#include "Constants.h"
#include "Map.h"

struct BulletInfo
{
																						 //D R A W 
	float radius;																		 //radius of the circle										 
	sf::Color color;																	 //color of the circle										  

																						 //R P G 
	float damage;																		 //damage                                                     
	float velocity;																		 //velocity (as sum of velocityX and velocityY vector value)  
	float attackSpeed;																	 //how much time in seconds must pass between shots           
};

class Bullet
{
  private:
																						 //D R A W
	  sf::CircleShape body;																 //sfml circle to draw

																						 //U P D A T E
	  float velocityY;																	 //velocity on OY
	  float velocityX;																	 //velocity on OX
	  float posX;																		 //x position
	  float posY;																		 //y position
	  Map* map;																             //points on map object so class can use Map methods (is_terrain())

																						 //C O M M O N
	  BulletInfo* info;																	 //pointer for single struct common for whole vector of bullets

  public:

	  Bullet(Map* map,sf::Vector2i pointPos, sf::Vector2f playerPos, BulletInfo* info);

	  void update(float dt);															 //updating postion
	  void draw(sf::RenderWindow& window);												 //drawing
	  bool is_to_destroy();																 //true if bullet leaves map or hits terrain, and you can remove it

	  sf::Vector2f get_position();														 //return vector with postion

	  ~Bullet();
	 
};

