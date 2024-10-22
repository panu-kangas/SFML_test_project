#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <fstream>
# include <vector>
# include <SFML/Graphics.hpp>

# include "Constants.hpp"
# include "Snake.hpp"
# include "Tower.hpp"

//////////

struct mapTile
{
	char	type; // 0 = grass, 1 = wall, C = Collectible
	bool	isApple;

	sf::Sprite	sprite;

};

//////////

class Map
{
	private:

	int	mapWidth;
	int	mapHeight;

	sf::Texture	wallTexture;
	sf::Texture	grassTexture;
	sf::Texture	appleTexture;
	sf::Texture	towerTexture;
	sf::Texture towerWeaponText[2];
	sf::Texture	arrowTexture;

	sf::Vector2f snakeStartPos;

	std::vector<std::vector<mapTile>>	wholeMapVec;
	std::vector<Tower>					towerVec;

	void	readMapInfo(std::string filename);
	void	checkValidMap(std::string mapStr, int rowLen); // Needs extra checks!!
	void	setWholeMapVec(std::string mapStr, int rowLen);
	void	setSnakeAndTowerPos();

//	void	drawTowers(sf::RenderWindow &window, sf::Vector2f snakePos); // --> Move to GameHandler
	int		checkTowerCollision(Snake &snake, sf::Vector2i snakeTileCoord);


	public:

	Map();
	~Map();

	void	initMap(std::string filename);
	void	drawMap(sf::RenderWindow &window, sf::Vector2f snakePos, int *xDrawLim, \
				int *yDrawLim, int gameState);

	void	resetMap();


	int		checkCollisions(Snake &snake);

	int		getMapWidth();
	int		getMapHeight();

	std::vector<Tower>	*getTowerVec();
	sf::Vector2f		&getSnakeStartPos();
	sf::Texture			&getWallTexture();
	sf::Texture			&getGrassTexture();
	mapTile				&getTileInfo(int x, int y);


};

#endif