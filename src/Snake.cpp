#include "Snake.hpp"

// Constructor

Snake::Snake()
{
	this->curDirection = -1;
	this->newDirection = -1;
	this->moveSpeed = SNAKE_INIT_SPEED;
	this->bodyCount = 3;
	this->startMoving = false;
	this->isBoosting = false;
	this->bodyReady = false;
	this->boostCounter = BOOST_MAX;

}


// Functionalities


void	Snake::initSnake(sf::RenderWindow &window, sf::Vector2f startPos, int mapWidth, int mapHeight)
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
	for (int i = 0; i < this->bodyCount; i++)
	{
		if (i == 0)
			this->bodyVec[i].setNextBody(&this->bodyVec[i + 1]);
		else if (i == bodyCount - 1)
			this->bodyVec[i].setPrevBody(&this->bodyVec[i - 1]);
		else
		{
			this->bodyVec[i].setNextBody(&this->bodyVec[i + 1]);
			this->bodyVec[i].setPrevBody(&this->bodyVec[i - 1]);
		}
	}

}

void	Snake::drawSnake(sf::RenderWindow &window, int gameState)
{
	if (gameState == GameOver)
	{
		snakeHeadSprite.setColor(sf::Color::Red);
		for (SnakeBody &temp : bodyVec)
			temp.getSprite().setColor(sf::Color::Red);
	}

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

void	Snake::moveSnake(int mapWidth, int mapHeight, float dt)
{
	int 	x = 0;
	int		y = 0;

	if (this->startMoving == false)
		return ;

	if (this->curDirection != this->newDirection)
	{
		this->curDirection = this->newDirection;
		this->bodyVec[0].addTurn(newDirection, sf::Vector2i(snakeWorldCoord.x, snakeWorldCoord.y));
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

	if (bodyReady == true)
		checkBoost(dt);

	this->snakeWorldCoord.x += x * moveSpeed * dt;
	this->snakeWorldCoord.y += y * moveSpeed * dt;

	this->setSpritePosition(mapWidth, mapHeight);

	for (int i = 0; i < this->bodyCount; i++)
		this->bodyVec[i].moveSnakeBody(mapWidth, mapHeight, this->snakeWorldCoord, dt);

	if (bodyReady == false && !bodyVec.empty() && bodyVec.back().getMoveSpeedCounter() == 0)
		bodyReady = true;

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



/*
	BOOST HANDLING
*/


void	Snake::checkBoost(float dt)
{
	if (isBoosting == true && moveSpeed == SNAKE_INIT_SPEED)
		setSpeed(SNAKE_BOOST_SPEED);
	else if (isBoosting == false && moveSpeed == SNAKE_BOOST_SPEED)
		setSpeed(SNAKE_INIT_SPEED);

	if (moveSpeed == SNAKE_INIT_SPEED && boostCounter < BOOST_MAX)
		boostCounter += dt * BOOST_REPLENISH;
	else if (moveSpeed == SNAKE_BOOST_SPEED && boostCounter > 0)
		boostCounter -= dt * BOOST_REDUCE;
	else if (boostCounter <= 0)
		isBoosting = false;

}


/*
	SETTERS
*/

void	Snake::setSpeed(int newSpeed)
{
	moveSpeed = newSpeed;
	for (SnakeBody &temp : bodyVec)
		temp.setSpeed(newSpeed);
}

void	Snake::setBoostStatus(bool status)
{
	isBoosting = status;
}

void	Snake::resetSnake(sf::Vector2f startPos, int mapWidth, int mapHeight)
{
	curDirection = -1;
	newDirection = -1;
	moveSpeed = SNAKE_INIT_SPEED;
	bodyCount = 3;
	startMoving = false;
	isBoosting = false;
	bodyReady = false;
	boostCounter = BOOST_MAX;
	snakeHeadSprite.setColor(sf::Color::White);
	bodyVec.clear();

/*
	snakeWorldCoord.x = startPos.x * TILE_SIZE;
	snakeWorldCoord.y = startPos.y * TILE_SIZE;
	setSpritePosition(mapWidth, mapHeight);

	for (SnakeBody &temp : bodyVec)
	{
		temp.resetBody(startPos);
		temp.getSprite().setColor(sf::Color::White);
	}
*/

}




/*
	GETTERS
*/

int			Snake::getMoveSpeed()
{
	return (moveSpeed);
}


sf::Sprite &Snake::getSnakeSprite()
{
	return (this->snakeHeadSprite);
}

sf::Vector2f Snake::getSnakeWorldCoord()
{
	return (this->snakeWorldCoord);
}

std::vector<SnakeBody>	&Snake::getBodyVec()
{
	return (bodyVec);
}


bool	Snake::getStartMovingStatus()
{
	return (this->startMoving);
}

bool	Snake::getBoostStatus()
{
	return (isBoosting);
}

float	Snake::getBoostCounter()
{
	return (boostCounter);
}




