#include "Animation.h"



Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
	:imageCount{imageCount},switchTime{switchTime},totalTime{0.f}
{
	currentImage.x = 0;

	uvRect.width = texture->getSize().x / static_cast<int>(imageCount.x);
	uvRect.height = texture->getSize().y / static_cast<int>(imageCount.y);
}

void Animation::update(int row, float dt, bool faceRight)
{
	currentImage.y = row;
	totalTime += dt;
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime; 
		currentImage.x++;

		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}

	uvRect.top = currentImage.y * uvRect.height;

	if (faceRight)
	{
		uvRect.left = currentImage.x * uvRect.width; 
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}

}

Animation::~Animation()
{
}