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
	if (!this->wallTexture.loadFromFile("sprites/wall.png") \
	|| !this->grassTexture.loadFromFile("sprites/grass.png") \
	|| !this->appleTexture.loadFromFile("sprites/apple.png"))
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

	if (checkValidMap(mapStr, rowLen) == 1)
	{
		std::cerr << RED << "\nMap-file error: map not surrounded with walls.\n"
		<< "Exiting program.\n" << RESET << std::endl;
		exit (1);
	}

	this->mapWidth = rowLen;
	this->mapHeight = mapHeightCounter;

	setTileVec(mapStr, rowLen);
	setSnakeStartPos();

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
				tileVec[y][x].sprite.setTexture(this->wallTexture);
			else if (tileVec[y][x].type == '0' || tileVec[y][x].type == 'C' \
			|| tileVec[y][x].type == 'S')
				tileVec[y][x].sprite.setTexture(this->grassTexture);
			
			tileVec[y][x].sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
			window.draw(tileVec[y][x].sprite);

			if (tileVec[y][x].type == 'C')
			{
				tileVec[y][x].sprite.setTexture(this->appleTexture);
				window.draw(tileVec[y][x].sprite);
			}
		}
	}
	
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

	for (int y = snakeTileCoord.y - 1; y < snakeTileCoord.y + 2; y++)
	{
		for (int x = snakeTileCoord.x - 1; x < snakeTileCoord.x + 2; x++)
		{	
			if (x >= 0 && x < this->mapWidth && y >= 0 && y < this->mapHeight)
			{
				if (tileVec[y][x].type == '1')
				{
					if (tileVec[y][x].sprite.getGlobalBounds().intersects(snakeSprite.getGlobalBounds()))
						return (1);
				}
				else if (tileVec[y][x].type == 'C')
				{
					if (tileVec[y][x].sprite.getGlobalBounds().intersects(snakeSprite.getGlobalBounds()))
					{
						tileVec[y][x].type = '0';
						return (2);
					}
				}
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

sf::Vector2i &Map::getSnakeStartPos()
{
	return (this->snakeStartPos);
}


void	Map::setSnakeStartPos()
{
	for (int y = 0; y < tileVec.size(); y++)
	{
		for (int x = 0; x < tileVec[y].size(); x++)
		{
			if (tileVec[y][x].type == 'S')
			{
				this->snakeStartPos.x = x;
				this->snakeStartPos.y = y;
			}
		}
	}
}

