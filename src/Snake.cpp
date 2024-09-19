#include "Snake.hpp"

// Constructor

Snake::Snake()
{
	direction = 0;
	moveSpeed = 20;

	std::cout << "Snake got created" << std::endl;
}


// Functionalities


void	Snake::Init(sf::RenderWindow &window)
{
	if (!headTexture.loadFromFile("sprites/snake_head.png"))
	{
		std::cerr << "Texture loading failed. Exiting program!" << std::endl;
		exit (1);
	};

	snakeSprite.setTexture(headTexture);

	sf::Vector2u windowSize = window.getSize();
	snakeSprite.setPosition(windowSize.x / 2, windowSize.y / 2);
}

void	Snake::drawSnake(sf::RenderWindow &window)
{
	window.draw(snakeSprite);
}

void	Snake::changeDirection(sf::Event &keypress)
{
	switch (keypress.key.scancode)
	{
		case sf::Keyboard::Scan::W :
			direction = 0;
			break ;
		case sf::Keyboard::Scan::D :
			direction = 1;
			break ;
		case sf::Keyboard::Scan::S :
			direction = 2;
			break ;
		case sf::Keyboard::Scan::A :
			direction = 3;
			break ;
		default:
			return ;
	}
}

void	Snake::moveSnake()
{
	int x = 0;
	int y = 0;

	if (snakeClock.getElapsedTime().asMilliseconds() < 500)
		return ;


	switch (this->direction)
	{
		case 0 :
			y = -1;
			break ;
		case 1 :
			x = 1;
			break ;
		case 2 :
			y = 1;
			break ;
		case 3 :
			x = -1;
			break ;
		default:
			x = 0;
	}

	snakeSprite.move(x * moveSpeed, y * moveSpeed);
	snakeClock.restart();

}
