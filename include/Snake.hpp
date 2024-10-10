#ifndef SNAKE_HPP
# define SNAKE_HPP

# include <iostream>
# include <vector>
# include <SFML/Graphics.hpp>

# include "Constants.hpp"
# include "SnakeBody.hpp"


class Snake
{
	private:

	sf::Texture	snakeHeadTexture;
	sf::Sprite	snakeHeadSprite;
	sf::Clock	snakeClock;

	sf::Texture				bodyTexture;
	std::vector<SnakeBody>	bodyVec;
	int						bodyCount;

	bool		startMoving;

	int			curDirection; // 0 up, 1 right, 2 down, 3 left
	int			newDirection;
	int			moveSpeed;

	sf::Vector2f	snakeWorldCoord; // in pixels!

	void	setSpritePosition(int mapWidth, int mapHeight);

	public:

	Snake();
	~Snake() {};

	void	initSnake(sf::RenderWindow &window, sf::Vector2i startPos, int mapWidth, int mapHeight);
	void	drawSnake(sf::RenderWindow &window);
	void	moveSnake(int mapWidth, int mapHeight);
	void	changeDirection(sf::Event &keypress);

	sf::Sprite		&getSnakeSprite();
	sf::Vector2f	getSnakeWorldCoord();
	bool			getStartMovingStatus();
};

#endif