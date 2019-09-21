#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <fstream>
#include <iostream>
class Map
{
  private:
	  int mapArray[MAP_SIZE_X][MAP_SIZE_Y];												 //array that keeps types of tiles							

	  sf::RectangleShape mapDrawer;														 //rectangle for map drawing
	  sf::Color color;																	 //color of mapDrawer

	  enum type																			 //types of tiles
	  {
		blank = 0,
		block1,
		block2,
		block3,
	  };
  public:
	  Map();

	  void draw(sf::RenderWindow& window,float camX);								     //drawing map (x)-camera x postion
	  void set_tile(int x, int y, int type);											 //sets (type) of tile with coords (x) and (y)
	  void set_tile(float x, float y, int type);										 //sets (type) of tile containing (x) and (y) as a global mouse position
	  bool is_terrain(float x, float y);												 //return true if tile containing (x) and (y) isn't blank
	  void load_from_file(std::string filename="1");									 //loading map from file with (fileName) as name

	  ~Map();
};

