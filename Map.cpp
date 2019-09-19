#include "Map.h"

Map::Map() : mapArray{ 0 },mapDrawer{sf::Vector2f(GRID,GRID)},color{sf::Color(0,0,0)}
{
	for (int y = 15; y < MAP_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_SIZE_X; x++)
			mapArray[x][y] = block1;
	}

	mapArray[30][14] = block2;
	mapArray[60][12] = block3;
	mapArray[95][11] = block1;
}

void Map::draw(sf::RenderWindow& window,float camX)
{
	for (int y = 0; y < MAP_SIZE_Y; y++)
	{
		for (int x = static_cast<int>(camX/60) - SCREEN_WIDTH/2/60; x < static_cast<int>(camX / 60) + SCREEN_WIDTH/2/60 + 1; x++)
		{
			switch (mapArray[x][y])
			{
			case blank:
			{
				color = sf::Color(30, 30, 30); break;
			}
			case block1:
			{
				color = sf::Color(120, 50, 50); break;
			}
			case block2:
			{
				color = sf::Color(50, 120, 50); break;
			}
			case block3:
			{
				color = sf::Color(50, 50, 120); break;
			}
			}
			mapDrawer.setFillColor(color);
			mapDrawer.setPosition(static_cast<float>(x * GRID), static_cast<float>(y * GRID));
			window.draw(mapDrawer);
		}
	}
}

void Map::set_tile(int x, int y, int type)
{
	if (x < 0 || y < 0 || x>MAP_SIZE_X-1 || y> MAP_SIZE_Y-1 || type < blank || type>block1)
		return;

	mapArray[x][y] = type;
}

void Map::set_tile(float x, float y, int type)
{
	if (x < 0 || y < 0 || x>MAP_SIZE_X*GRID || y> MAP_SIZE_Y*GRID || type < blank || type>block3)
		return;

	mapArray[static_cast<int>(x / 60)][static_cast<int>(y / 60)] = type;
}

bool Map::is_terrain(float x, float y)
{
	if (x<0 || x>MAP_SIZE_X * GRID || y<0 || y> MAP_SIZE_X * GRID)
		return false;

	if(mapArray[static_cast<int>(x/60.f)][static_cast<int>(y/60.f)]==0)
		return false;
	else
		return true;
}

Map::~Map()
{
}
