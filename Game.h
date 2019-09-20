#pragma once
#include "Textures.h"
#include "Map.h"
#include "Camera.h"
#include "Player.h"
#include <SFML/Graphics.hpp>


class Game
{
  private:
	  Textures textures;																 //class that keeps and loads all textures
	  Map map;
	  Camera camera;
	  Player player;
	  
	  sf::Clock clock;																	 //clock that measures times of each frame

  public:
	  Game(Textures* textures);

	  int play();													                     //play a single level

	  ~Game();


};

