#ifndef SNAKE_HPP
# define SNAKE_HPP

# include <iostream>
# include <SFML/Graphics.hpp>

class Snake
{
	private:

	sf::Texture	headTexture;
	sf::Sprite	snakeSprite;
	sf::Clock	snakeClock;
	int			direction; // 0 up, 1 right, 2 down, 3 left
	int			moveSpeed;

	public:

	Snake();
	~Snake() {std::cout << "Snake got destroyed" << std::endl;};

	void	Init(sf::RenderWindow &window);
	void	drawSnake(sf::RenderWindow &window);
	void	moveSnake();
	void	changeDirection(sf::Event &keypress);
};

#endif