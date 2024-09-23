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

void	SnakeBody::InitBody(sf::RenderWindow &window, sf::Texture &bodyText, int num)
{
	sf::Vector2u windowSize = window.getSize();

	this->bodySprite.setTexture(bodyText);
	this->bodySprite.setPosition(windowSize.x / 2, (windowSize.y / 2) + (TILE_SIZE * (num + 1))); // need to change this

	this->bodyNum = num;
}

void	SnakeBody::drawSnakeBody(sf::RenderWindow &window)
{
	window.draw(this->bodySprite);
}

void	SnakeBody::moveSnakeBody()
{
	int		x = 0;
	int 	y = 0;

	if (!this->newDirVec.empty() && !this->turnPointVec.empty())
	{
		sf::Vector2f checkVec = this->bodySprite.getPosition();

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

	this->bodySprite.move(x * moveSpeed, y * moveSpeed);

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
