#include "Snake.hpp"

// Constructor

Snake::Snake()
{
	direction = 0;
	moveSpeed = 4;

	std::cout << "Snake got created" << std::endl;
}


// Functionalities


void	Snake::Init(sf::RenderWindow &window)
{
	if (!snakeHeadTexture.loadFromFile("sprites/snake_head.png"))
	{
		std::cerr << "Texture loading failed. Exiting program!" << std::endl;
		exit (1);
	};

	snakeHeadSprite.setTexture(snakeHeadTexture);

	sf::Vector2u windowSize = window.getSize();
	snakeHeadSprite.setPosition(windowSize.x / 2, windowSize.y / 2);
}

void	Snake::drawSnake(sf::RenderWindow &window)
{
	window.draw(snakeHeadSprite);
}

void	Snake::changeDirection(sf::Event &keypress)
{
	int	temp_dir = this->direction;
	int	check_dir;

	switch (keypress.key.scancode)
	{
		case sf::Keyboard::Scan::W :
			this->direction = 0;
			break ;
		case sf::Keyboard::Scan::D :
			this->direction = 1;
			break ;
		case sf::Keyboard::Scan::S :
			this->direction = 2;
			break ;
		case sf::Keyboard::Scan::A :
			this->direction = 3;
			break ;
		default:
			return ;
	}

	check_dir = direction - 2;
	if (check_dir < 0)
		check_dir = 4 + check_dir;

	if (temp_dir == check_dir)
		this->direction = temp_dir;

}

void	Snake::moveSnake()
{
	int x = 0;
	int y = 0;

	if (snakeClock.getElapsedTime().asMilliseconds() < 50)
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

	snakeHeadSprite.move(x * moveSpeed, y * moveSpeed);
	snakeClock.restart();

}

// Utils

int	Snake::checkSnakePos()
{
	sf::Vector2f snakePos = snakeHeadSprite.getPosition();

	if (snakePos.x <= TILE_SIZE || snakePos.x >= WINDOW_WIDTH - (TILE_SIZE * 2)
	|| snakePos.y <= TILE_SIZE || snakePos.y >= WINDOW_HEIGHT - (TILE_SIZE * 2))
		return (1);
	else
		return (0);

}

