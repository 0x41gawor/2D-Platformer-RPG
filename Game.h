#pragma once
#include "Textures.h"
#include "Map.h"
#include "Camera.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <fstream>


class Game
{
  private:

	  Textures textures;																 //class that keeps and loads all textures
	  Map map;
	  Camera camera;
	  Player player;
	  
	  sf::Clock clock;																	 //clock that measures times of each frame
	  sf::Sprite cursor;																 //instead of system cursor

  public:

	  Game(Textures* textures);

	  int play();													                     //play a single level
	  std::string setup_player(std::string username ="user");							 //setups player members and returns path for level file

	  ~Game();


};

