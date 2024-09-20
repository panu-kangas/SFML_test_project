#include "Map.hpp"

// Constructor && Destructor

Map::Map()
{
	// std::cout << "Map got created" << std::endl;
}

Map::~Map()
{
	// std::cout << "Map got destroyed" << std::endl;
}


// Initialization

void	Map::initMap(std::string filename)
{
	if (!wallTexture.loadFromFile("sprites/wall.png") || !grassTexture.loadFromFile("sprites/grass.png"))
	{
		std::cerr << "\nTexture loading failed. Exiting program!\n" << std::endl;
		exit (1);
	};

	this->tilesOnScreen = (WINDOW_WIDTH / TILE_SIZE) * (WINDOW_HEIGHT / TILE_SIZE); // is this needed...?

	readMapInfo(filename);
}

void	Map::readMapInfo(std::string filename)
{
	std::ifstream	inputFile(filename);
	std::string		tempStr = "";
	std::string		mapStr = "";
	int				rowLen = 0;

	if (!inputFile.is_open())
	{
		std::cerr << RED << "\nMap-file error: could not open file.\n"
		<< "Exiting program.\n" << RESET << std::endl;
		exit (1);
	}

	while (std::getline(inputFile, tempStr))
	{
		if (mapStr.empty())
			rowLen = tempStr.length();
		
		if (rowLen == tempStr.length())
			mapStr += tempStr;
		else
		{
			std::cerr << RED << "\nMap-file error: given map is not rectangular\n"
			<< "Exiting program.\n" << RESET << std::endl;
			exit (1);
		}
	}

	if (mapStr.empty())
	{
		std::cerr << RED << "\nMap-file error: empty mapfile given.\n"
		<< "Exiting program.\n" << RESET << std::endl;
		exit (1);
	}

	if (checkValidMap(mapStr, rowLen) == 1)
	{
		std::cerr << RED << "\nMap-file error: map not surrounded with walls.\n"
		<< "Exiting program.\n" << RESET << std::endl;
		exit (1);
	}

	setTileVec(mapStr, rowLen);

}

int		Map::checkValidMap(std::string mapStr, int rowLen)
{
	for (int i = 0; i < mapStr.length(); i++)
	{
		if ((i < rowLen || i >= mapStr.length() - rowLen) && mapStr[i] != '1')
			return (1);
		else if ((i % rowLen == 0 || i % rowLen == rowLen - 1) && mapStr[i] != '1')
			return (1);
	}

	return (0);

	// I might need some extra checks here...? 
	// Example: player is totally blocked by walls etc
}


void	Map::setTileVec(std::string mapStr, int rowLen)
{
	int		k = 0;
	mapTile tile = {'0'};
	std::vector<mapTile> tempVec;

	for (int i = 0; i < mapStr.length(); i++)
	{
		tile.type = mapStr[i];
		tempVec.push_back(tile);

		k++;
		if (k == rowLen)
		{
			tileVec.push_back(tempVec);
			tempVec.clear();
			k = 0;
		}
	}
}


// Drawing

void	Map::drawMap(sf::RenderWindow &window)
{
	for (int y = 0; y < tileVec.size(); y++)
	{
		for (int x = 0; x < tileVec[y].size(); x++)
		{	
			if (tileVec[y][x].type == '1')
			{
				tileVec[y][x].sprite.setTexture(this->wallTexture);
				tileVec[y][x].sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
				window.draw(tileVec[y][x].sprite);
			}
			else if (tileVec[y][x].type == '0')
			{
				tileVec[y][x].sprite.setTexture(this->grassTexture);
				tileVec[y][x].sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
				window.draw(tileVec[y][x].sprite);
			}
		}
	}
	
}


// Collision detection


int		Map::checkWallCollisions(sf::Sprite &snakeSprite)
{
	for (int y = 0; y < tileVec.size(); y++)
	{
		for (int x = 0; x < tileVec[y].size(); x++)
		{	
			if (tileVec[y][x].type == '1')
			{
				if (tileVec[y][x].sprite.getGlobalBounds().intersects(snakeSprite.getGlobalBounds()))
					return (1);
			}
		}
	}

	return (0);
}



// Utils

char	Map::getTileType(int x, int y)
{
	return (tileVec[y][x].type);
}




/* OLD VERSION

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
*/