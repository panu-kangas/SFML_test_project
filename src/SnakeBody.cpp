#include "SnakeBody.hpp"

/*
	CONSTRUCTOR
*/

SnakeBody::SnakeBody()
{
	this->curDirection = -1;
	this->moveSpeed = SNAKE_INIT_SPEED;
	this->nextBody = nullptr;
	prevBody = nullptr;
}


/*
	INIT
*/

void	SnakeBody::InitBody(sf::RenderWindow &window, sf::Texture &bodyText, sf::Vector2i startPos, int num)
{
	// sf::Vector2u windowSize = window.getSize();

	this->bodySprite.setTexture(bodyText);

	this->bodyWorldCoord.x = startPos.x * TILE_SIZE;
	this->bodyWorldCoord.y = startPos.y * TILE_SIZE;

	this->bodyNum = num;
	this->moveStartCounter = -2;
}

void	SnakeBody::drawSnakeBody(sf::RenderWindow &window)
{
	window.draw(this->bodySprite);
}


/*
	MOVING FUNCTIONS
*/

void	SnakeBody::moveSnakeBody(int mapWidth, int mapHeight, sf::Vector2f snakeHeadPos, float dt)
{
	int		x = 0;
	int 	y = 0;

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


	if (moveStartCounter == -2)
		moveStartCounter = ((TILE_SIZE * (bodyNum + 1)) / (moveSpeed * dt)) + (1 * (bodyNum + 1));
	else if (this->moveStartCounter > 0)
		this->moveStartCounter--;
	else
	{
		this->bodyWorldCoord.x += x * moveSpeed * dt;
		this->bodyWorldCoord.y += y * moveSpeed * dt;
	
		if (!this->newDirVec.empty() && !this->turnPointVec.empty())
		{	
			if (checkTurningPoint())
			{
				if (nextBody != nullptr)
					nextBody->addTurn(newDirVec[0], sf::Vector2i(bodyWorldCoord.x, bodyWorldCoord.y));
				this->curDirection = this->newDirVec[0];
				this->newDirVec.erase(this->newDirVec.begin()); // use deque...?
				this->turnPointVec.erase(this->turnPointVec.begin()); // use deque...?
			}
		}
		else
		{
			// Fixing the position to be exactly TILE_SIZE pixels away from previous body
			// MAKE THIS SEPARATE PRIVATE FUNCTION!

			sf::Vector2f relativePos;

			if (prevBody == nullptr)
				relativePos = snakeHeadPos;
			else
				relativePos = prevBody->getBodyCoord();

			if (curDirection == 0)
				bodyWorldCoord.y = relativePos.y + TILE_SIZE;
			else if (curDirection == 1)
				bodyWorldCoord.x = relativePos.x - TILE_SIZE;
			else if (curDirection == 2)
				bodyWorldCoord.y = relativePos.y - TILE_SIZE;
			else if (curDirection == 3)
				bodyWorldCoord.x = relativePos.x + TILE_SIZE;
		}

	}


	// Should this be separate function...?
	
	int drawCoordX = this->bodyWorldCoord.x - (snakeHeadPos.x - (16 * TILE_SIZE));
	int drawCoordY = this->bodyWorldCoord.y - (snakeHeadPos.y - (11 * TILE_SIZE));

	if (snakeHeadPos.x - (16 * TILE_SIZE) < 0)
		drawCoordX += snakeHeadPos.x - (16 * TILE_SIZE);
	else if (snakeHeadPos.x + (17 * TILE_SIZE) > (mapWidth * TILE_SIZE))
		drawCoordX += (snakeHeadPos.x + (17 * TILE_SIZE)) - (mapWidth * TILE_SIZE);

	if (snakeHeadPos.y - (11 * TILE_SIZE) < 0)
		drawCoordY += snakeHeadPos.y - (11 * TILE_SIZE);
	else if (snakeHeadPos.y + (12 * TILE_SIZE) > (mapHeight * TILE_SIZE))
		drawCoordY += (snakeHeadPos.y + (12 * TILE_SIZE)) - (mapHeight * TILE_SIZE);


	this->bodySprite.setPosition(drawCoordX, drawCoordY);

}


bool	SnakeBody::checkTurningPoint()
{
	if (curDirection == -1)
		return (true);

	if (curDirection == 0 && bodyWorldCoord.y <= turnPointVec[0].y)
	{
		if (newDirVec[0] == 1)
			bodyWorldCoord.x += turnPointVec[0].y - bodyWorldCoord.y;
		else
			bodyWorldCoord.x -= turnPointVec[0].y - bodyWorldCoord.y;

		bodyWorldCoord.y = turnPointVec[0].y;

		return (true);
	}
	else if (curDirection == 1 && bodyWorldCoord.x >= turnPointVec[0].x)
	{
		if (newDirVec[0] == 0)
			bodyWorldCoord.y -= bodyWorldCoord.x - turnPointVec[0].x;
		else
			bodyWorldCoord.y += bodyWorldCoord.x - turnPointVec[0].x;

		bodyWorldCoord.x = turnPointVec[0].x;
		return (true);
	}
	else if (curDirection == 2 && bodyWorldCoord.y >= turnPointVec[0].y)
	{
		if (newDirVec[0] == 1)
			bodyWorldCoord.x += bodyWorldCoord.y - turnPointVec[0].y;
		else
			bodyWorldCoord.x -= bodyWorldCoord.y - turnPointVec[0].y;

		bodyWorldCoord.y = turnPointVec[0].y;

		return (true);
	}
	else if (curDirection == 3 && bodyWorldCoord.x <= turnPointVec[0].x)
	{
		if (newDirVec[0] == 0)
			bodyWorldCoord.y -= turnPointVec[0].x - bodyWorldCoord.x;
		else
			bodyWorldCoord.y += turnPointVec[0].x - bodyWorldCoord.x;

		bodyWorldCoord.x = turnPointVec[0].x;
		return (true);
	}

	return (false);
}


/*
	SETTERS
*/

void	SnakeBody::setSpeed(int newSpeed)
{
	moveSpeed = newSpeed;
}

void	SnakeBody::setNextBody(SnakeBody *next)
{
	this->nextBody = next;
}

void	SnakeBody::setPrevBody(SnakeBody *prev)
{
	prevBody = prev;
}


void	SnakeBody::addTurn(int direction, sf::Vector2i turnPoint)
{
	this->newDirVec.push_back(direction);
	this->turnPointVec.push_back(turnPoint);
}


/*
	GETTERS
*/

sf::Sprite	&SnakeBody::getSprite()
{
	return (bodySprite);
}

int			SnakeBody::getMoveSpeedCounter()
{
	return (moveStartCounter);
}

sf::Vector2f	&SnakeBody::getBodyCoord()
{
	return (bodyWorldCoord);
}






