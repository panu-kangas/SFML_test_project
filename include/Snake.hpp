#ifndef SNAKE_HPP
# define SNAKE_HPP

# include <iostream>
# include "Map.hpp"
# include <SFML/Graphics.hpp>

class Snake
{
	private:

	sf::Texture	snakeHeadTexture;
	sf::Sprite	snakeHeadSprite;
	sf::Clock	snakeClock;

	int			direction; // 0 up, 1 right, 2 down, 3 left
	int			prev_direction;
	int			moveSpeed;
	int			coordX; // coord in the middle of snake head
	int			coordY; // coord in the middle of snake head

	public:

	Snake();
	~Snake() {};

	void	Init(sf::RenderWindow &window);
	void	drawSnake(sf::RenderWindow &window);
	void	moveSnake();
	void	changeDirection(sf::Event &keypress);

	sf::Sprite &getSnakeSprite();
};

#endif