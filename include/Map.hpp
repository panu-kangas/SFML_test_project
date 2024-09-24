#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <fstream>
# include <vector>
# include <SFML/Graphics.hpp>

# include "Constants.hpp"
# include "Snake.hpp"

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

	sf::Vector2i snakeStartPos;

	std::vector<std::vector<mapTile>>	tileVec; // Optimization: make this an array (use new)

	void	readMapInfo(std::string filename);
	int		checkValidMap(std::string mapStr, int rowLen); // might need extra checks...?
	void	setTileVec(std::string mapStr, int rowLen);
	void	setSnakeStartPos();

	public:

	Map();
	~Map();

	void	initMap(std::string filename);
	void	drawMap(sf::RenderWindow &window);

	int		checkCollisions(Snake &snake);

	char	getTileType(int x, int y);
	sf::Vector2i &getSnakeStartPos();

};

#endif