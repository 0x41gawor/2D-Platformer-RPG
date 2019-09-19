#pragma once
#include<SFML/Graphics.hpp>
#include "Constants.h"
class Camera
{
  private:
	  sf::View view;												                     //game window view
	  float posX;																		 //x position of camera
	  const float posY;																	 //y position of camera (const becasue on OY whole map is seen without dragging)

	  float lastMouseX;																	 //mouse x position form last loop
	  float currentMouseX;																 //current mouse x postion

	  float dx;																			 //diffrence beetwen lastMousX and mouseX showing hot much move view
  public:
	  Camera();

	  void update(sf::RenderWindow& window);											 //update what part of map is shown on the screen
	  float get_posX();																	 //returns global x postion of camera
	  void set_posX(float x);															 //sets global x position of camera

	  ~Camera();





};

