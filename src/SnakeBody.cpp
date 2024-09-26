#include "SnakeBody.hpp"

// Constructor

SnakeBody::SnakeBody()
{
	this->curDirection = 0;
	this->moveSpeed = 4;
	this->nextBody = nullptr;

	// std::cout << "SnakeBody got created" << std::endl;
}


// Functionalities

void	SnakeBody::InitBody(sf::RenderWindow &window, sf::Texture &bodyText, sf::Vector2i startPos, int num)
{
	sf::Vector2u windowSize = window.getSize();

	this->bodySprite.setTexture(bodyText);
//	this->bodySprite.setPosition(startPos.x * TILE_SIZE, startPos.y * TILE_SIZE);

	this->bodyWorldCoord.x = startPos.x * TILE_SIZE;
	this->bodyWorldCoord.y = startPos.y * TILE_SIZE;

	this->bodyNum = num;
	this->moveStartCounter = ((num + 1) * TILE_SIZE) / this->moveSpeed; // Check this formula later
}

void	SnakeBody::drawSnakeBody(sf::RenderWindow &window)
{
	window.draw(this->bodySprite);
}

void	SnakeBody::moveSnakeBody(int mapWidth, int mapHeight, sf::Vector2f snakeHeadPos)
{
	int		x = 0;
	int 	y = 0;

	if (!this->newDirVec.empty() && !this->turnPointVec.empty())
	{
		sf::Vector2f checkVec(this->bodyWorldCoord.x, this->bodyWorldCoord.y);

		if (checkVec.x == this->turnPointVec[0].x \
		&& checkVec.y == this->turnPointVec[0].y)
		{
			this->curDirection = this->newDirVec[0];
			this->newDirVec.erase(this->newDirVec.begin()); // use deque...?
			this->turnPointVec.erase(this->turnPointVec.begin()); // use deque...?
		}
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

	if (this->moveStartCounter > 0)
		this->moveStartCounter--;
	else
	{
		this->bodyWorldCoord.x += x * moveSpeed;
		this->bodyWorldCoord.y += y * moveSpeed;
	}

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

// Utils


void	SnakeBody::addTurn(int direction, sf::Vector2f turnPoint)
{
	this->newDirVec.push_back(direction);
	this->turnPointVec.push_back(turnPoint);
}

void	SnakeBody::setNextBody(SnakeBody *next)
{
	this->nextBody = next;
}
