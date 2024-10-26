#include "Arrow.hpp"


Arrow::Arrow(sf::Vector2f initCoord, sf::Texture &texture, sf::Vector2f snakePos) : arrowVel(220.0)
{
	coord = initCoord;
	
	homeTower = sf::FloatRect({coord.x - 32, coord.y - 17}, {64, 64});

	float	len;

	dirVec.x = (snakePos.x + TILE_SIZE / 2) - coord.x;
	dirVec.y = (snakePos.y + TILE_SIZE / 2) - coord.y;

	len = sqrtf(powf(dirVec.x, 2) + powf(dirVec.y, 2));

	dirVec.x = dirVec.x / len;
	dirVec.y = dirVec.y / len;

	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

	// TEST (make separate function)

	float		radToDegMultiplier = 180.0 / PI;

	if (dirVec.x == 0)
	{
		if (dirVec.y < 0)
			angle = 0;
		else
			angle = 180;
		return ;
	}
	else if (dirVec.y == 0)
	{
		if (dirVec.x < 0)
			angle = 270;
		else
			angle = 90;
		return ;
	}

	if (dirVec.x > 0)
		angle = 90.0 + radToDegMultiplier * atan(dirVec.y / dirVec.x);
	else
		angle = 270.0 + radToDegMultiplier * atan(dirVec.y / dirVec.x);

	// TEST END


	// Small nudge to make it more realistic

	coord.x += 10 * dirVec.x;
	coord.y += 10 * dirVec.y;

}



/*
	MOVE ARROWS
*/

void	Arrow::moveArrow(float dt)
{
	coord.x += arrowVel * dirVec.x * dt;
	coord.y += arrowVel * dirVec.y * dt;
}

/*
	DRAW ARROWS
*/

void	Arrow::drawArrow(sf::RenderWindow &window, int &drawX, int &drawY)
{
	sprite.setPosition(drawX, drawY);
	sprite.setRotation(angle);

	window.draw(sprite);
}



/*
	GETTERS
*/

sf::Vector2f	&Arrow::getCoord()
{
	return (coord);
}

sf::Vector2f	&Arrow::getDirVec()
{
	return (dirVec);
}

sf::Sprite		&Arrow::getSprite()
{
	return (sprite);
}

sf::Vector2f	Arrow::getArrowTipCoord()
{
	sf::Vector2f arrowTipCoord;

	arrowTipCoord = coord;

	arrowTipCoord.x += dirVec.x * (6 / 2);
	arrowTipCoord.y += dirVec.y * (30 / 2);

	return (arrowTipCoord);
}

sf::FloatRect	&Arrow::getHomeTower()
{
	return (homeTower);
}




