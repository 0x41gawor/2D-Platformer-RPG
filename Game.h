#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Camera.h"
class Game
{
  private:
	  Map map;
	  Camera camera;

  public:
	  Game();
	  int play();													                     //play a single level

	  ~Game();


};

