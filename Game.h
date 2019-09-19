#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
class Game
{
  private:
	  Map map;

  public:
	  Game();
	  int play();													//play a single level

	  ~Game();


};

