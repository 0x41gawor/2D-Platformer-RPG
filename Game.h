#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>

#include "Textures.h"
#include "Map.h"
#include "Camera.h"
#include "Player.h"
#include "healthBar.h"

class Game
{
  private:

	  Textures textures;																 //class that keeps and loads all textures
	  Map map;
	  Camera camera;
	  Player player;
	  healthBar playerHealthBar;

	  
	  sf::Clock clock;																	 //clock that measures times of each frame
	  sf::Sprite cursor;																 //instead of system cursor

  public:

	  Game(Textures* textures);

	  int play();													                     //play a single level
	
	  ~Game();


};

