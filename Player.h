#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Map.h"

class Player
{
private:
																	                     //D R A W
	sf::RectangleShape body;															 //rectangle to draw player
	float width;																		 //lengths of this rectangle
	float height;																		 //.|.

																						 //G R A V I T Y	
	float movementSpeed;	                                                             //MS from boots / velocity on OX
	float mass;				                                                             //mass
	float velocityY;		                                                             //velocity on OY
	float jumpForce;		                                                             //how high player is jumping
	bool onGround;			                                                             //true if player is on ground and there no need to move him down
																							
																						 //C O L L I S I O N
	Map* map;																			 //points on map object so class can use Map methods (is_terrain())
	sf::Vector2f lastPos;																 //postion from last frame to possibly recover it
	float a;																			 //temporarily here to set finaly values
	float b;																			 //used to define position of 8 points around player
	float c;																			 //these points detect collsion with map
	float d;																			 //.|.
	bool leftBanned;																	 //they forbid movement in specified direction if there is a wall
	bool rightBanned;																	 //.|.

public:
	Player(Map* map);

	void update(const float& dt);														 //udpate
	void draw(sf::RenderWindow&);														 //drawing player
	void apply_force(float force);														 //makes player move upwards
	void collision();																	 //position correction taking into account map collsion after update

	~Player();
};	