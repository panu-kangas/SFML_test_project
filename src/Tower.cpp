#include "Tower.hpp"


// Constructor

Tower::Tower(sf::Texture &towerText, sf::Texture *weaponTextArr, sf::Texture *arrowText, sf::Vector2f towerCoord)
{
	this->weaponAngle = 0;
	this->weaponIdleAngle = 0;
	this->idleAngleIncrement = 1;

	this->attackRadius = 4 * TILE_SIZE;
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

void	Tower::shootArrow(sf::Vector2f snakePos)
{

	// Move arrow

	if (!this->arrowVec.empty())
	{
		for (int i = 0; i < this->arrowVec.size(); i++)
		{
			this->arrowVec[i].coord.x += ARROW_SPEED * this->arrowVec[i].dirVec.x;
			this->arrowVec[i].coord.y += ARROW_SPEED * this->arrowVec[i].dirVec.y; // make FPS independent
		}
	}
	
	// Move arrow end

	if (this->isShooting == false)
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
	else if (this->shootingClock.getElapsedTime().asSeconds() < 1.0) // make FPS independent
		return ;

	struct arrow tempArrow;

	tempArrow.angle = this->weaponAngle;
	tempArrow.coord = this->getPosInPixels();

	// TEST

	float	len;

	tempArrow.dirVec.x = snakePos.x - tempArrow.coord.x;
	tempArrow.dirVec.y = snakePos.y - tempArrow.coord.y;

	len = sqrtf(powf(tempArrow.dirVec.x, 2) + powf(tempArrow.dirVec.y, 2));

	tempArrow.dirVec.x = tempArrow.dirVec.x / len;
	tempArrow.dirVec.y = tempArrow.dirVec.y / len;


	// TEST END

	tempArrow.sprite.setTexture(*this->arrowTexture);
	this->arrowVec.push_back(tempArrow);

	this->weaponSprite.setTexture(this->weaponTextureArr[this->weaponAnimIterator]);
	this->weaponAnimIterator++;

	if (this->weaponAnimIterator == 2)
		this->weaponAnimIterator = 0;

	this->shootingClock.restart();

}


void	Tower::drawTower(sf::RenderWindow &window)
{
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

void	Tower::setIdleAngle()
{
	if (this->towerClock.getElapsedTime().asMilliseconds() < 30)
		return ;

	this->weaponSprite.setTexture(this->weaponTextureArr[0]);

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

	// 16 = half of snake width/height, 32 = half of tower width/height
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


