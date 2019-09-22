#include "Map.h"

Map::Map() : mapArray{ 0 },mapDrawer{sf::Vector2f(GRID,GRID)},color{sf::Color(0,0,0)}
{
	for (int y = 15; y < MAP_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_SIZE_X; x++)
			mapArray[x][y] = block1;
	}
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


bool Map::is_terrain(float x, float y)
{
	if (x<0 || x>MAP_SIZE_X * GRID || y<0 || y> MAP_SIZE_X * GRID)
		return false;

	if(mapArray[static_cast<int>(x/60.f)][static_cast<int>(y/60.f)]==0)
		return false;
	else
		return true;
}

void Map::load_from_file(std::string filename)
{
	std::ifstream file;

	filename += ".txt";

	try 
	{
		file.open(filename);

		if (!file)
			throw 404;

		int x{ 0 };
		int y{ 0 };

		std::string line{ "" };
		while (!file.eof())
		{
			getline(file, line);
			mapArray[x][y] = atoi(line.c_str());
			x++;
			if (x > MAP_SIZE_X-1)
			{
				x = 0; y++;
			}
		}
	}

	catch (int)
	{
		std::cerr << "No file found";
		return;
	}
}

Map::~Map()
{
}
