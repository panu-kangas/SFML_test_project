#include "Tower.hpp"


// Constructor

Tower::Tower(sf::Texture &towerText, sf::Texture &weaponText, sf::Vector2f towerCoord)
{
	this->weaponAngle = 0;
	this->weaponIdleAngle = 0;
	this->idleAngleIncrement = 1;

	this->attackRadius = 4 * TILE_SIZE; 

	this->towerSprite.setTexture(towerText);
	this->weaponSprite.setTexture(weaponText);
	this->weaponSprite.setOrigin(this->weaponSprite.getLocalBounds().width / 2, this->weaponSprite.getLocalBounds().height / 2);

	this->towerCoord = towerCoord;
}



// Functionalities



bool	Tower::isVisible(int *xDrawLimits, int *yDrawLimits)
{
	sf::Vector2f	pointsToCheck[4]; // in pixels

	for (int i = 0; i < 4; i++)
	{
		pointsToCheck[i] = this->towerCoord;
		pointsToCheck[i].x *= TILE_SIZE;
		pointsToCheck[i].y *= TILE_SIZE;
	}

	pointsToCheck[1].x += (TILE_SIZE * 2);

	pointsToCheck[2].x += (TILE_SIZE * 2);
	pointsToCheck[2].y += (TILE_SIZE * 2);

	pointsToCheck[3].y += (TILE_SIZE * 2);

	for (int i = 0; i < 4; i++)
	{
		if (pointsToCheck[i].x > xDrawLimits[0] && pointsToCheck[i].x < xDrawLimits[1] \
		&& pointsToCheck[i].y > yDrawLimits[0] && pointsToCheck[i].y < yDrawLimits[1])
			return (true);
	}

	return (false);
}


bool	Tower::isSnakeVisible(sf::Vector2f snakeWorldCoord)
{
	// 64 is tower width & height

	if (snakeWorldCoord.x > ((this->towerCoord.x * TILE_SIZE) - this->attackRadius) \
	&& snakeWorldCoord.x < ((this->towerCoord.x * TILE_SIZE) + 64 + this->attackRadius) \
	&& snakeWorldCoord.y > ((this->towerCoord.y * TILE_SIZE) - this->attackRadius) \
	&& snakeWorldCoord.y < ((this->towerCoord.y * TILE_SIZE) + 64 + this->attackRadius))
		return (true);
	else
		return (false);
}



void	Tower::drawTower(sf::RenderWindow &window)
{
	window.draw(this->towerSprite);
	window.draw(this->weaponSprite);
}


// Getters && Setters

void	Tower::setAngle(int newAngle)
{
	this->weaponAngle = newAngle;
}

void	Tower::setIdleAngle()
{
	if (this->towerClock.getElapsedTime().asMilliseconds() < 30)
		return ;

	if (this->weaponIdleAngle == 45)
		this->idleAngleIncrement = -1;
	else if (this->weaponIdleAngle == 315)
		this->idleAngleIncrement = 1;

	this->weaponIdleAngle += this->idleAngleIncrement;

	if (this->weaponIdleAngle > 360)
		this->weaponIdleAngle -= 360;
	else if (this->weaponIdleAngle < 0)
		this->weaponIdleAngle += 360;

	this->weaponAngle = this->weaponIdleAngle;

	this->towerClock.restart();

}


void	Tower::setAttackAngle(sf::Vector2f snakePos)
{
	sf::Vector2f diffVec;
	float		radToDegMultiplier = 180.0 / PI;

	diffVec.x = snakePos.x - ((this->towerCoord.x * TILE_SIZE) + 32); // 32 = half of tower width
	diffVec.y = snakePos.y - ((this->towerCoord.y * TILE_SIZE) + 32); // 32 = half of tower width

//	std::cout << "DIFFVEC: x = " << diffVec.x << " y = " << diffVec.y << std::endl;

	/* 
	THE FOLLOWING DOES NOT WORK!! Fix it later
	*/

	this->weaponAngle = radToDegMultiplier * atan(diffVec.y / diffVec.x);

//	if (diffVec.x > 0 && diffVec.y < 0)
//		this->weaponAngle *= -1;

	std::cout << "ANGLE: " << this->weaponAngle << std::endl;


}


sf::Vector2f	Tower::getPosInPixels()
{
	sf::Vector2f temp(this->towerCoord.x * TILE_SIZE, this->towerCoord.y * TILE_SIZE);

	return (temp);
}

sf::Sprite	&Tower::getSprite()
{
	return (this->towerSprite);
}

sf::Sprite	&Tower::getWeaponSprite()
{
	return (this->weaponSprite);
}

int			&Tower::getWeaponAngle()
{
	return (this->weaponAngle);
}


