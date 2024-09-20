#include "Snake.hpp"

// Constructor

Snake::Snake()
{
	direction = 0;
	prev_direction = 0;
	moveSpeed = 4;

	// std::cout << "Snake got created" << std::endl;
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

	coordX = (windowSize.x / 2) + (TILE_SIZE / 2); // These need to be set based on the map!!
	coordY = (windowSize.y / 2) + (TILE_SIZE / 2); // These need to be set based on the map!!
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
	else
		this->prev_direction = temp_dir;

}

void	Snake::moveSnake()
{
	int x = 0;
	int y = 0;
	int	moveDir;

	if (snakeClock.getElapsedTime().asMilliseconds() < 25)
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

	coordX += (x * moveSpeed);
	coordY += (y * moveSpeed);

	snakeClock.restart();

}

// Utils

sf::Sprite &Snake::getSnakeSprite()
{
	return (this->snakeHeadSprite);
}


