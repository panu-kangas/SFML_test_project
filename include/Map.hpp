#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <fstream>
# include <vector>
# include <SFML/Graphics.hpp>

# define WINDOW_WIDTH	1024
# define WINDOW_HEIGHT	736
# define TILE_SIZE		32

# define RED "\033[31m"
# define GREEN "\033[32m"
# define RESET "\033[0m"

//////////

struct mapTile
{
	char	type; // 0 = grass, 1 = wall

	sf::Sprite	sprite;

};

//////////

class Map
{
	private:

	int	tilesOnScreen;

	sf::Texture	wallTexture;
	sf::Texture	grassTexture;
	std::vector<std::vector<mapTile>>	tileVec;

	void	readMapInfo(std::string filename);
	int		checkValidMap(std::string mapStr, int rowLen); // might need extra checks...?
	void	setTileVec(std::string mapStr, int rowLen);

	public:

	Map();
	~Map();

	void	initMap(std::string filename);
	void	drawMap(sf::RenderWindow &window);

	int		checkWallCollisions(sf::Sprite &snakeSprite);

	char	getTileType(int x, int y);

};

#endif