#pragma once
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Map.h"
#include "Animation.h"
#include "Bullet.h"

class Player
{
  private:
																	                     //D R A W
	sf::RectangleShape body;															 //rectangle to draw player
	float width;																		 //lengths of this rectangle
	float height;																		 //.|.

																						 //A N I M A T I O N
	Animation animation;																 //instance of animation handling class
	int texRow;																		     //current row of texture to animate
	bool faceRigt;																	     //if true texture is loaded from left to right, if false right to left

																						 //G R A V I T Y	
	float movementSpeed;	                                                             //MS from boots / velocity on OX
	float mass;				                                                             //mass
	float velocityY;		                                                             //velocity on OY
	float jumpForce;		                                                             //how high player is jumping
	bool onGround;			                                                             //true if player is on ground and there no need to move him down
	sf::Vector2f movement;																 //movement in each frame
																							
																						 //C O L L I S I O N
	Map* map;																			 //points on map object so class can use Map methods (is_terrain())
	sf::Vector2f pos;																     //position after update() 
	bool leftBanned;																	 //they forbid movement in specified direction if there is a wall
	bool rightBanned;																	 //.|.

																						 //R P G
	float health;																		 //health
	float ATK;																			 //atk - multiples bullet damage

public:																				     //S H O O T I N G
	BulletInfo bulletInfo;																 //struct for keeping common variables for bullets
	std::vector<Bullet> gun;															 //vector of bullets
	float lastShotTime;																	 //keeps time passed from last act of firing a gun

  public:

	Player(Map* map, sf::Texture* texture, sf::Vector2u imageCount = sf::Vector2u(3, 4), float switchTime = 0.3f);

	void update(const float& dt);														 //udpate
	void draw(sf::RenderWindow&);														 //drawing player
	void apply_force(float force);														 //makes player move upwards
	void collision();																	 //position correction taking into account map collsion after update
	bool is_shoot_ok();																	 //true if time passed since last shot is higher than attackspeed
	void reset_lastShotTime();															 //sets lastShotTime value as 0.f
	void load_from_file(std::string username);											 //loads player variables from file
	void take_damage(float dmg);														 //decreases players health by (dmg)

	sf::Vector2f get_position();													     //returns vector2f of player postion
	float get_bullet_damage();															 //returns bullet damage multiplied by ATK
	float get_health();																	 //returns current health

	void print_info();																	 //printing stats in console (for debugging)
	
	~Player();
};	