#include "Map.hpp"
#include "Tower.hpp"

// Constructor && Destructor

Map::Map()
{
	if (!this->wallTexture.loadFromFile("sprites/wall.png") \
	|| !this->grassTexture.loadFromFile("sprites/grass.png") \
	|| !this->appleTexture.loadFromFile("sprites/apple.png") \
	|| !this->towerTexture.loadFromFile("sprites/tower_base.png") \
	|| !this->towerWeaponText[0].loadFromFile("sprites/tower_weapon.png") \
	|| !this->towerWeaponText[1].loadFromFile("sprites/tower_weapon_1.png") \
	|| !this->arrowTexture.loadFromFile("sprites/arrow.png"))
	{
		std::cerr << "\nTexture loading failed. Exiting program!\n" << std::endl;
		exit (1);
	};
	
	appleCount = 0;
	mapWidth = 0;
	mapHeight = 0;
}

Map::~Map()
{
}


// Initialization

void	Map::initMap(std::string filename)
{
	// CHECK THIS 

	readMapInfo(filename);
}

void	Map::readMapInfo(std::string filename)
{
	std::ifstream	inputFile(filename);
	std::string		tempStr = "";
	std::string		mapStr = "";
	int				rowLen = 0;
	int				mapHeightCounter = 0;

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
		mapHeightCounter++;
	}

	if (mapStr.empty())
	{
		std::cerr << RED << "\nMap-file error: empty mapfile given.\n"
		<< "Exiting program.\n" << RESET << std::endl;
		exit (1);
	}

	checkValidMap(mapStr, rowLen);

	this->mapWidth = rowLen;
	this->mapHeight = mapHeightCounter;

	if (mapWidth < 33 || mapHeight < 23)
	{
		std::cerr << RED << "\nMap-file error: map too small. Minimum width is 33 tiles, minimum height is 23 tiles.\n"
		<< "Exiting program.\n" << RESET << std::endl;
		exit (1);
	}

	this->setWholeMapVec(mapStr, rowLen);
	this->setSnakeAndTowerPos();
}

void	Map::checkValidMap(std::string mapStr, int rowLen)
{
	bool	snakeFound = false;

	for (int i = 0; i < mapStr.length(); i++)
	{
		if ((i < rowLen || i >= mapStr.length() - rowLen) && mapStr[i] != '1')
		{
			std::cerr << RED << "\nMap-file error: map not surrounded with walls.\n"
			<< "Exiting program.\n" << RESET << std::endl;
			exit (1);
		}
		else if ((i % rowLen == 0 || i % rowLen == rowLen - 1) && mapStr[i] != '1')
		{
			std::cerr << RED << "\nMap-file error: map not surrounded with walls.\n"
			<< "Exiting program.\n" << RESET << std::endl;
			exit (1);
		}

		if (mapStr[i] == 'S')
		{
			if (snakeFound == false)
				snakeFound = true;
			else
			{
				std::cerr << RED << "\nMap-file error: map has multiple snakes ('S').\n"
				<< "Exiting program.\n" << RESET << std::endl;
				exit (1);
			}
		}
		

	}

	// I might need some extra checks here...? 
	// 1. No Towers next to each other
	// 2. No snake close to tower
}


void	Map::setWholeMapVec(std::string mapStr, int rowLen)
{
	int			k = 0;
	mapTile		tile;
	std::string	ValidMapCharacters = VALID_MAP_CHAR;
	std::vector<mapTile> tempVec;

	for (int i = 0; i < mapStr.length(); i++)
	{
		if (ValidMapCharacters.find_first_of(mapStr[i]) == ValidMapCharacters.npos)
		{
			std::cerr << RED << "\nMap-file error: map has invalid character(s).\n"
			<< "Exiting program.\n" << RESET << std::endl;
			exit (1);
		}

		tile.type = mapStr[i];

		if (tile.type == 'C')
		{
			appleCount++;
			tile.isApple = true;
		}
		else
			tile.isApple = false;

		if (tile.type == '1')
			tile.sprite.setTexture(this->wallTexture);
		else if (tile.type == '0' || tile.type == 'C' || tile.type == 'S' || tile.type == 'T')
			tile.sprite.setTexture(this->grassTexture);

		tempVec.push_back(tile);

		k++;
		if (k == rowLen)
		{
			wholeMapVec.push_back(tempVec);
			tempVec.clear();
			k = 0;
		}
	}
}


// Drawing

void	Map::drawMap(sf::RenderWindow &window, sf::Vector2f snakePos, int *xDrawLim, \
int *yDrawLim, int gameState)
{
	bool	sideWallOnScreen = false;
	bool	topBottomWallOnScreen = false;

	if (xDrawLim[0] <= 0 || xDrawLim[0] == (mapWidth * TILE_SIZE) - (WINDOW_WIDTH))
		sideWallOnScreen = true;
	if (yDrawLim[0] <= 0 || yDrawLim[0] == (mapHeight * TILE_SIZE) - WINDOW_HEIGHT)
		topBottomWallOnScreen = true;
	

	int	windowX, windowY, windowXStart;

	if (sideWallOnScreen == true)
		windowX = 0;
	else
		windowX = ((int)snakePos.x % TILE_SIZE) * -1;

	windowXStart = windowX;


	if (topBottomWallOnScreen == true)
		windowY = 0;
	else
		windowY = ((int)snakePos.y % TILE_SIZE) * -1;


	for (int y = yDrawLim[0] / TILE_SIZE; y < yDrawLim[1] / TILE_SIZE; ++y)
	{
		windowX = windowXStart;
		for (int x = xDrawLim[0] / TILE_SIZE; x < xDrawLim[1] / TILE_SIZE; ++x)
		{	
			wholeMapVec[y][x].sprite.setPosition(windowX, windowY);

			// End screen coloring
			if (gameState == GameOver)
				wholeMapVec[y][x].sprite.setColor(sf::Color::Red);

			window.draw(wholeMapVec[y][x].sprite);

			if (wholeMapVec[y][x].isApple == true)
			{
				wholeMapVec[y][x].sprite.setTexture(this->appleTexture);
				window.draw(wholeMapVec[y][x].sprite);
				wholeMapVec[y][x].sprite.setTexture(this->grassTexture);
			}

			windowX += TILE_SIZE;
		}
		windowY += TILE_SIZE;
	}
	
}


/*
	RESET MAP
*/

void	Map::resetMap()
{
	appleCount = 0;
	towerVec.clear();
	wholeMapVec.clear();
}




// Collision detection


int		Map::checkCollisions(Snake &snake)
{
	sf::Vector2i snakeTileCoord;
	sf::Vector2f snakeWorldCoord;
	sf::Sprite snakeSprite = snake.getSnakeSprite();

	snakeWorldCoord = snake.getSnakeWorldCoord();
	snakeTileCoord.x = snakeWorldCoord.x / TILE_SIZE;
	snakeTileCoord.y = snakeWorldCoord.y / TILE_SIZE;

	for (int y = snakeTileCoord.y - 1; y < snakeTileCoord.y + 2; ++y)
	{
		for (int x = snakeTileCoord.x - 1; x < snakeTileCoord.x + 2; ++x)
		{	
			if (x >= 0 && x < this->mapWidth && y >= 0 && y < this->mapHeight)
			{
				if (wholeMapVec[y][x].type == '1')
				{
					if (wholeMapVec[y][x].sprite.getGlobalBounds().intersects(snakeSprite.getGlobalBounds()))
						return (1);
				}
				else if (wholeMapVec[y][x].isApple == true)
				{
					if (wholeMapVec[y][x].sprite.getGlobalBounds().intersects(snakeSprite.getGlobalBounds()))
					{
						wholeMapVec[y][x].isApple = false;
						return (2);
					}
				}
			}
		}
	}

	if (this->checkTowerCollision(snake, snakeTileCoord) == 1)
		return (1);

	return (0);
}


int		Map::checkTowerCollision(Snake &snake, sf::Vector2i snakeTileCoord)
{
	for (int i = 0; i < this->towerVec.size(); i++)
	{
		if (this->towerVec[i].getSprite().getPosition().x != -100 \
		&& this->towerVec[i].getSprite().getGlobalBounds().intersects(snake.getSnakeSprite().getGlobalBounds()))
			return (1);
	}

	return (0);
}

/*
	UTILS
*/


sf::Vector2f &Map::getSnakeStartPos()
{
	return (this->snakeStartPos);
}

int		Map::getMapWidth()
{
	return (this->mapWidth);
}

int		Map::getMapHeight()
{
	return (this->mapHeight);
}

std::vector<Tower>	*Map::getTowerVec()
{
	return (&towerVec);
}

sf::Texture	&Map::getWallTexture()
{
	return (wallTexture);
}

sf::Texture	&Map::getGrassTexture()
{
	return (grassTexture);
}

mapTile		&Map::getTileInfo(int x, int y)
{
	return (wholeMapVec[y][x]);
}

int			Map::getAppleCount()
{
	return (appleCount);
}




/*
	SETTER
*/


void	Map::setSnakeAndTowerPos()
{
	for (int y = 0; y < wholeMapVec.size(); y++)
	{
		for (int x = 0; x < wholeMapVec[y].size(); x++)
		{
			if (wholeMapVec[y][x].type == 'S')
			{
				this->snakeStartPos.x = x;
				this->snakeStartPos.y = y;
			}
			else if (wholeMapVec[y][x].type == 'T')
				this->towerVec.push_back(Tower(this->towerTexture, this->towerWeaponText, &this->arrowTexture, sf::Vector2f(x, y)));
		}
	}
}



