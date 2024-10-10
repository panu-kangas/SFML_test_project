#include "Snake.hpp"

// Constructor

Snake::Snake()
{
	this->curDirection = 0;
	this->newDirection = 0;
	this->moveSpeed = MOVE_SPEED;
	this->bodyCount = 3;
	this->startMoving = false;

}


// Functionalities


void	Snake::initSnake(sf::RenderWindow &window, sf::Vector2i startPos, int mapWidth, int mapHeight)
{
	if (!this->snakeHeadTexture.loadFromFile("sprites/snake_head.png") \
	|| !this->bodyTexture.loadFromFile("sprites/snake_body.png"))
	{
		std::cerr << RED << "Texture loading failed. Exiting program!" << RESET << std::endl;
		exit (1);
	};

	this->snakeHeadSprite.setTexture(snakeHeadTexture);

	this->snakeWorldCoord.x = startPos.x * TILE_SIZE;
	this->snakeWorldCoord.y = startPos.y * TILE_SIZE;

	this->setSpritePosition(mapWidth, mapHeight);

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

	if (this->startMoving == true)
	{
		int	check_dir;

		check_dir = this->newDirection - 2;
		if (check_dir < 0)
			check_dir = 4 + check_dir;

		if (this->curDirection == check_dir)
			this->newDirection = this->curDirection;
	}
	else
		this->startMoving = true;

}

void	Snake::moveSnake(int mapWidth, int mapHeight)
{
	int 	x = 0;
	int		y = 0;

	if (this->snakeClock.getElapsedTime().asMilliseconds() < 20 || this->startMoving == false)
		return ;

	if (this->curDirection != this->newDirection)
	{
		this->curDirection = this->newDirection;
		for (int i = 0; i < this->bodyCount; i++)
			this->bodyVec[i].addTurn\
			(this->newDirection, sf::Vector2f(this->snakeWorldCoord.x, this->snakeWorldCoord.y));
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

/*
OLD VERSION

	if (((this->curDirection == 0 || this->curDirection == 2) && topBottomWallOnScreen == true) \
	|| ((this->curDirection == 1 || this->curDirection == 3) && sideWallOnScreen == true))
	{
		this->snakeHeadSprite.move(x * moveSpeed, y * moveSpeed);
	}
*/

	this->snakeWorldCoord.x += x * moveSpeed;
	this->snakeWorldCoord.y += y * moveSpeed;

	this->setSpritePosition(mapWidth, mapHeight);


	for (int i = 0; i < this->bodyCount; i++)
		this->bodyVec[i].moveSnakeBody(mapWidth, mapHeight, this->snakeWorldCoord);

	this->snakeClock.restart();

}

void	Snake::setSpritePosition(int mapWidth, int mapHeight)
{
	int drawCoordX = this->snakeWorldCoord.x - (snakeWorldCoord.x - (16 * TILE_SIZE));
	int drawCoordY = this->snakeWorldCoord.y - (snakeWorldCoord.y - (11 * TILE_SIZE));

	if (snakeWorldCoord.x - (16 * TILE_SIZE) < 0)
		drawCoordX += snakeWorldCoord.x - (16 * TILE_SIZE);
	else if (snakeWorldCoord.x + (17 * TILE_SIZE) > (mapWidth * TILE_SIZE))
		drawCoordX += (snakeWorldCoord.x + (17 * TILE_SIZE)) - (mapWidth * TILE_SIZE);

	if (snakeWorldCoord.y - (11 * TILE_SIZE) < 0)
		drawCoordY += snakeWorldCoord.y - (11 * TILE_SIZE);
	else if (snakeWorldCoord.y + (12 * TILE_SIZE) > (mapHeight * TILE_SIZE))
		drawCoordY += (snakeWorldCoord.y + (12 * TILE_SIZE)) - (mapHeight * TILE_SIZE);

	this->snakeHeadSprite.setPosition(drawCoordX, drawCoordY);
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

bool	Snake::getStartMovingStatus()
{
	return (this->startMoving);
}



