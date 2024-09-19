#include "Map.hpp"

Map::Map()
{
	std::cout << "Map got created" << std::endl;
}

Map::~Map()
{
	std::cout << "Map got destroyed" << std::endl;
}


void	Map::initMap()
{
	if (!wallTexture.loadFromFile("sprites/wall.png") || !grassTexture.loadFromFile("sprites/grass.png"))
	{
		std::cerr << "Texture loading failed. Exiting program!" << std::endl;
		exit (1);
	};

	for (int y = 0; y < WINDOW_HEIGHT; y += TILE_SIZE)
	{
		if (y == 0 || y == WINDOW_HEIGHT - TILE_SIZE)
		{
			for (int x = 0; x < WINDOW_WIDTH; x += TILE_SIZE)
			{
				tileArr[x / TILE_SIZE][y / TILE_SIZE].setTexture(wallTexture);
				tileArr[x / TILE_SIZE][y / TILE_SIZE].setPosition(x, y);
			}
		}
		else
		{
			for (int x = 0; x < WINDOW_WIDTH; x += TILE_SIZE)
			{
				if (x == 0 || x == WINDOW_WIDTH - TILE_SIZE)
				{
					tileArr[x / TILE_SIZE][y / TILE_SIZE].setTexture(wallTexture);
					tileArr[x / TILE_SIZE][y / TILE_SIZE].setPosition(x, y);
				}
				else
				{
					tileArr[x / TILE_SIZE][y / TILE_SIZE].setTexture(grassTexture);
					tileArr[x / TILE_SIZE][y / TILE_SIZE].setPosition(x, y);
				}
			}
		}
	}
}

void	Map::drawMap(sf::RenderWindow &window)
{
	for (int y = 0; y < WINDOW_HEIGHT / TILE_SIZE; y++)
	{
		for (int x = 0; x < WINDOW_WIDTH / TILE_SIZE; x++)
			window.draw(tileArr[x][y]);
	}
}



// Utils