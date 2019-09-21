#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Map.h"
#include <cmath>

class Bullet
{
  private:
																						 //D R A W
	  sf::CircleShape body;																 //sfml circle to draw
	  int radius;																		 //radius of the circle										  !?!
	  sf::Color color;																	 //color of the circle										  !?!

																						 //U P D A T E
	  float velocityY;																	 //velocity on OY
	  float velocityX;																	 //velocity on OX
	  float posX;																		 //x position
	  float posY;																		 //y position
	  Map* map;																             //points on map object so class can use Map methods (is_terrain())

																						 //R P G 
	  float damage;																		 //damage                                                     !?!
	  float velocity;																	 //velocity (as sum of velocityX and velocityY vector value)  !?!
	  float attackSpeed;																 //how much time in seconds must pass between shots           !?!

  public:

	  Bullet(Map* map,sf::Vector2i pointPos, sf::Vector2f playerPos);

	  void update();																	 //updating postion
	  void draw(sf::RenderWindow& window);												 //drawing
	  sf::Vector2f get_position();														 //return vector with postion
	  bool is_to_destroy();																 //true if bullet leaves map or hits terrain, and you can remove it
	  float get_damage();																 //return damage
	  void set_damage(float);															 //bunch of setters
	  void set_velocity(float);															 //.|.
	  void set_attackSpeed(float);														 //.|.
	  void set_radius(int);																 //.|.
	  void set_color(sf::Color);														 //.|.

	  ~Bullet();
	  /*
		Every player, skeleteon and cannon on map is going to have its own vector of bullets (as a member of its class).
		Members marked with "!?!" in comment section are gonna to be common with the whole vector, so its necessary to find an idea to not create
		5 unnecessary variables for each object in the vector. It's going to be a big memory issue.

		Static was examined and it is not a good idea.
	  */
};

