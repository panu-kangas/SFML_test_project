#include "Arrow.hpp"


Arrow::Arrow(int initAngle, sf::Vector2f initCoord, sf::Texture &texture, sf::Vector2f snakePos)
{
	angle = initAngle; // is this needed...?
	coord = initCoord;

	float	len;

	dirVec.x = (snakePos.x + TILE_SIZE / 2) - coord.x;
	dirVec.y = (snakePos.y + TILE_SIZE / 2) - coord.y;

	len = sqrtf(powf(dirVec.x, 2) + powf(dirVec.y, 2));

	dirVec.x = dirVec.x / len;
	dirVec.y = dirVec.y / len;

	sprite.setTexture(texture);

}



/*
	MOVE ARROWS
*/

void	Arrow::moveArrow()
{
	// make FPS independent !!

	coord.x += ARROW_SPEED * dirVec.x;
	coord.y += ARROW_SPEED * dirVec.y;
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

