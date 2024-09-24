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

	int			curDirection; // 0 up, 1 right, 2 down, 3 left
	int			newDirection;
	int			moveSpeed;

	sf::Vector2f	snakeWorldCoord; // in pixels!

	public:

	Snake();
	~Snake() {};

	void	Init(sf::RenderWindow &window, sf::Vector2i startPos);
	void	drawSnake(sf::RenderWindow &window);
	void	moveSnake();
	void	changeDirection(sf::Event &keypress);

	sf::Sprite		&getSnakeSprite();
	sf::Vector2f	getSnakeWorldCoord();
};

#endif