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
																							
																						 //C O L L I S I O N
	Map* map;																			 //points on map object so class can use Map methods (is_terrain())
	sf::Vector2f lastPos;																 //postion from last frame to possibly recover it
	float a;																			 //temporarily here to set final values
	float b;																			 //used to define position of 8 points around player
	float c;																			 //these points detect collsion with map
	float d;																			 //.|.
	bool leftBanned;																	 //they forbid movement in specified direction if there is a wall
	bool rightBanned;																	 //.|.

  public:																				 //S H O O T I N G
	BulletInfo bulletInfo;																 //struct for keeping common variables for bullets
	std::vector<Bullet> gun;															 //vector of bullets
	float lastShotTime;																	 //keeps time passed from last act of firing a gun

  public:

	Player(Map* map, sf::Texture* texture, sf::Vector2u imageCount = sf::Vector2u(3, 4), float switchTime = 0.3f);

	void update(const float& dt);														 //udpate
	void draw(sf::RenderWindow&);														 //drawing player
	void apply_force(float force);														 //makes player move upwards
	void collision();																	 //position correction taking into account map collsion after update
	void load_bulletInfo_from_file(std::string filename="");							 //loads bulletInfo from file with (filename) as name	
	bool is_shoot_ok();																	 //true if time passed since last shot is higher than attackspeed
	void reset_lastShotTime();															 //sets lastShotTime value as 0.f

	sf::Vector2f get_postion();													         //returnrs vector2f of player postion

	~Player();
};	