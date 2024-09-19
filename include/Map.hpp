#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <vector>

# include <SFML/Graphics.hpp>

# define WINDOW_WIDTH	1024
# define WINDOW_HEIGHT	736
# define TILE_SIZE		32

class Map
{
	private:

	sf::Texture	wallTexture;
	sf::Texture	grassTexture;
	sf::Sprite	tileArr[WINDOW_WIDTH / TILE_SIZE][WINDOW_HEIGHT / TILE_SIZE];

	public:

	Map();
	~Map();

	void	initMap();
	void	drawMap(sf::RenderWindow &window);

};

#endif