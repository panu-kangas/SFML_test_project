#include "Tower.hpp"


// Constructor

Tower::Tower(sf::Texture &towerText, sf::Texture *weaponTextArr, sf::Texture *arrowText, sf::Vector2f towerCoord) : IdleAngleVelocity(30.0)
{
	this->weaponAngle = 0;
	this->weaponIdleAngle = 0;

	this->attackRadius = 8 * TILE_SIZE;
	this->isShooting = false;
	this->firstShotFired = false;
	this->weaponAnimIterator = 1;

	this->weaponTextureArr = weaponTextArr;
	this->arrowTexture = arrowText;

	this->towerSprite.setTexture(towerText);
	this->weaponSprite.setTexture(weaponTextArr[0]);
	this->weaponSprite.setOrigin(this->weaponSprite.getLocalBounds().width / 2, this->weaponSprite.getLocalBounds().height / 2);

	this->towerCoord = towerCoord;
}


/*
	VISIBILITY CHECKS
*/



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


/*
	SHOOTING ARROWS
*/

void	Tower::shootArrow(sf::Vector2f snakePos, std::vector<Arrow> &arrowVec, bool snakeMoveStat)
{
	if (this->isShooting == false || snakeMoveStat == false)
	{
		this->firstShotFired = false;
		return ;
	}
	else if (this->isShooting == true && this->firstShotFired == false)
	{
		this->shootingClock.restart();
		firstShotFired = true;
		return ;
	}
	else if (this->shootingClock.getElapsedTime().asSeconds() < 1.0)
		return ;

	this->weaponSprite.setTexture(this->weaponTextureArr[this->weaponAnimIterator]);
	this->weaponAnimIterator++;

	if (weaponAnimIterator == 2) // this value might be something different
	{
		arrowVec.push_back(Arrow(getMiddlePosInPixels(), *arrowTexture, snakePos));
		this->weaponAnimIterator = 0;
	}

	this->shootingClock.restart();

}


void	Tower::drawTower(sf::RenderWindow &window, int &drawX, int &drawY, sf::Vector2f snakePos, float dt)
{
	towerSprite.setPosition(drawX, drawY);

	weaponSprite.setPosition(drawX + 32, drawY + 17); // make universal...?
			
	if (isSnakeVisible(snakePos) == false)
	{
		setShootingFlag(false);
		setIdleAngle(dt);
	}
	else
	{
		setShootingFlag(true);
		if (weaponAnimIterator == 1)
			setAttackAngle(snakePos);
	}
	
	weaponSprite.setRotation(weaponAngle);

	window.draw(this->towerSprite);
	window.draw(this->weaponSprite);

}


/*
	SETTERS
*/

void	Tower::setAngle(int newAngle)
{
	this->weaponAngle = newAngle;
}

void	Tower::setIdleAngle(float dt)
{
	static float idleAngleIncrement;

	weaponSprite.setTexture(weaponTextureArr[0]);

	if (idleAngleIncrement == 0)
		idleAngleIncrement = IdleAngleVelocity * dt;
	else if (weaponIdleAngle >= 45 && weaponIdleAngle <= 47)
		idleAngleIncrement = IdleAngleVelocity * -1.0 * dt;
	else if (weaponIdleAngle >= 315 && weaponIdleAngle <= 317)
		idleAngleIncrement = IdleAngleVelocity * dt;

	weaponIdleAngle += idleAngleIncrement;

	if (weaponIdleAngle > 360)
		weaponIdleAngle -= 360;
	else if (weaponIdleAngle < 0)
		weaponIdleAngle += 360;

	weaponAngle = weaponIdleAngle;

}


void	Tower::setAttackAngle(sf::Vector2f snakePos)
{
	sf::Vector2f diffVec;
	float		radToDegMultiplier = 180.0 / PI;

	// 16 = half of snake width & height, 32 = half of tower width & height
	diffVec.x = (snakePos.x + 16) - ((this->towerCoord.x * TILE_SIZE) + 32);
	diffVec.y = (snakePos.y + 16) - ((this->towerCoord.y * TILE_SIZE) + 32);

	if (diffVec.x == 0)
	{
		if (diffVec.y < 0)
			this->weaponAngle = 0;
		else
			this->weaponAngle = 180;
		return ;
	}
	else if (diffVec.y == 0)
	{
		if (diffVec.x < 0)
			this->weaponAngle = 270;
		else
			this->weaponAngle = 90;
		return ;
	}

	if (diffVec.x > 0)
		this->weaponAngle = 90.0 + radToDegMultiplier * atan(diffVec.y / diffVec.x);
	else
		this->weaponAngle = 270.0 + radToDegMultiplier * atan(diffVec.y / diffVec.x);

}


void	Tower::setShootingFlag(bool value)
{
	this->isShooting = value;
}


/*
	GETTERS
*/

sf::Vector2f	Tower::getPosInPixels()
{
	sf::Vector2f temp(this->towerCoord.x * TILE_SIZE, this->towerCoord.y * TILE_SIZE);

	return (temp);
}

sf::Vector2f	Tower::getMiddlePosInPixels()
{
	sf::Vector2f temp(towerCoord.x * TILE_SIZE + 32, towerCoord.y * TILE_SIZE + 17);

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

float		&Tower::getWeaponAngle()
{
	return (this->weaponAngle);
}



