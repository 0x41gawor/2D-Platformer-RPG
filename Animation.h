#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
  private:

	sf::Vector2u imageCount;															 //(.x) how many colums (.y) how many rows textures has
	sf::Vector2u currentImage;															 //coords of current image

	float totalTime;                                                                     //time since last changed image
	float switchTime;                                                                    //time before one switch to the next image
public:
	sf::IntRect uvRect;                                                                  //current texture rectangle to display

  public:

	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);          //texure - address in memory, how many images, switch time

	void update(int row, float dt, bool faceRight);									     //row - row on texture to display, dt, is texture facing right
		
	~Animation();
};