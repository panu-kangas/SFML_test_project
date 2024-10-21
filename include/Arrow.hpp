#ifndef ARROW_HPP
# define ARROW_HPP

# include <iostream>
# include <vector>
# include <SFML/Graphics.hpp>

# include "Constants.hpp"


class Arrow
{
	private:

	int				angle; // is this needed...?
	sf::Vector2f	coord;
	sf::Vector2f	dirVec;
	sf::Sprite		sprite;

	float			arrowVel;

	public:

	Arrow(sf::Vector2f initCoord, sf::Texture &texture, sf::Vector2f snakePos);
	~Arrow() {};


	void	moveArrow(float dt);
	void	drawArrow(sf::RenderWindow &window, int &drawX, int &drawY);



	sf::Vector2f	&getCoord();
	sf::Vector2f	getArrowTipCoord();
	sf::Vector2f	&getDirVec();
	sf::Sprite		&getSprite();


};

#endif