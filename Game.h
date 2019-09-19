#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Camera.h"
#include "Player.h"
class Game
{
  private:
	  Map map;
	  Camera camera;
	  Player player;

	  sf::Clock clock;

  public:
	  Game();

	  int play();													                     //play a single level

	  ~Game();


};

