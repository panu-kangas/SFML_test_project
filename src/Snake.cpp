#include "Snake.hpp"

// Constructor

Snake::Snake()
{
	this->curDirection = 0;
	this->newDirection = 0;
	this->moveSpeed = 4;
	this->bodyCount = 3;

}


// Functionalities


void	Snake::Init(sf::RenderWindow &window, sf::Vector2i startPos)
{
	if (!this->snakeHeadTexture.loadFromFile("sprites/snake_head.png") \
	|| !this->bodyTexture.loadFromFile("sprites/snake_body.png"))
	{
		std::cerr << RED << "Texture loading failed. Exiting program!" << RESET << std::endl;
		exit (1);
	};

	this->snakeHeadSprite.setTexture(snakeHeadTexture);

	this->snakeHeadSprite.setPosition(startPos.x * TILE_SIZE, startPos.y * TILE_SIZE);

	this->snakeWorldCoord.x = startPos.x * TILE_SIZE;
	this->snakeWorldCoord.y = startPos.y * TILE_SIZE;


	SnakeBody tempBody;

	for (int i = 0; i < this->bodyCount; i++)
	{
		tempBody.InitBody(window, this->bodyTexture, startPos, i);
		this->bodyVec.push_back(tempBody);
	}
	for (int i = 0; i < this->bodyCount - 1; i++)
		this->bodyVec[i].setNextBody(&this->bodyVec[i + 1]);

}

void	Snake::drawSnake(sf::RenderWindow &window)
{
	for (int i = 0; i < this->bodyCount; i++)
		this->bodyVec[i].drawSnakeBody(window);
	window.draw(snakeHeadSprite);

}

void	Snake::changeDirection(sf::Event &keypress)
{
	switch (keypress.key.scancode)
	{
		case sf::Keyboard::Scan::W :
			this->newDirection = 0;
			break ;
		case sf::Keyboard::Scan::D :
			this->newDirection = 1;
			break ;
		case sf::Keyboard::Scan::S :
			this->newDirection = 2;
			break ;
		case sf::Keyboard::Scan::A :
			this->newDirection = 3;
			break ;
		default:
			return ;
	}

	int	check_dir;

	check_dir = this->newDirection - 2;
	if (check_dir < 0)
		check_dir = 4 + check_dir;

	if (this->curDirection == check_dir)
		this->newDirection = this->curDirection;

}

void	Snake::moveSnake()
{
	int 	x = 0;
	int		y = 0;

	if (snakeClock.getElapsedTime().asMilliseconds() < 25)
		return ;

	if (this->curDirection != this->newDirection)
	{
		this->curDirection = this->newDirection;
		for (int i = 0; i < this->bodyCount; i++)
			this->bodyVec[i].addTurn(this->newDirection, this->snakeHeadSprite.getPosition());
	}

	switch (this->curDirection)
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

	this->snakeHeadSprite.move(x * moveSpeed, y * moveSpeed);

	this->snakeWorldCoord.x += x * moveSpeed;
	this->snakeWorldCoord.y += y * moveSpeed;


	for (int i = 0; i < this->bodyCount; i++)
		this->bodyVec[i].moveSnakeBody();

	this->snakeClock.restart();

}

// Utils

sf::Sprite &Snake::getSnakeSprite()
{
	return (this->snakeHeadSprite);
}

sf::Vector2f Snake::getSnakeWorldCoord()
{
	return (this->snakeWorldCoord);
}


