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

	sf::Sprite	sprite;

};

//////////

class Map
{
	private:

	int	tilesOnScreen;
	int	mapWidth;
	int	mapHeight;

	sf::Texture	wallTexture;
	sf::Texture	grassTexture;
	sf::Texture	appleTexture;
	sf::Texture	towerTexture;
	sf::Texture towerWeaponText;

	sf::Vector2i snakeStartPos;

	std::vector<std::vector<mapTile>>	wholeMapVec; // Optimization: make this an array (use new)
	std::vector<Tower>					towerVec;

	int		xDrawLimits[2]; // in pixels!
	int		yDrawLimits[2]; // in pixels!
	bool	sideWallOnScreen;
	bool	topBottomWallOnScreen;

	void	readMapInfo(std::string filename);
	void	checkValidMap(std::string mapStr, int rowLen); // might need extra checks...?
	void	setWholeMapVec(std::string mapStr, int rowLen);
	void	setSnakeStartPos();

	void	setXLimits(sf::Vector2f snakePos);
	void	setYLimits(sf::Vector2f snakePos);

	void	drawTowers(sf::RenderWindow &window, sf::Vector2f snakePos);
	int		checkTowerCollision(Snake &snake, sf::Vector2i snakeTileCoord);


	public:

	Map();
	~Map();

	void	initMap(std::string filename);
	void	drawMap(sf::RenderWindow &window, Snake &snake);


	int		checkCollisions(Snake &snake);

//	char	getTileType(int x, int y);
	int		getMapWidth();
	int		getMapHeight();

	sf::Vector2i &getSnakeStartPos();
	void		setTowerVec();

};

#endif