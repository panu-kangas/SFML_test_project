#ifndef SNAKEBODY_HPP
# define SNAKEBODY_HPP

# include <iostream>
# include <vector>
# include <SFML/Graphics.hpp>

# include "Constants.hpp"

class SnakeBody
{
	private:

	sf::Sprite	bodySprite;
	SnakeBody	*nextBody;

	int			bodyNum;
	int			curDirection; // 0 up, 1 right, 2 down, 3 left
	int			moveSpeed;

	std::vector<int> 			newDirVec;
	std::vector<sf::Vector2f>	turnPointVec;


	public:

	SnakeBody();
	~SnakeBody() {};

	void	InitBody(sf::RenderWindow &window, sf::Texture &bodyText, int num);
	void	drawSnakeBody(sf::RenderWindow &window);
	void	moveSnakeBody();

	void	addTurn(int direction, sf::Vector2f turnPoint);
	void	setNextBody(SnakeBody *next);

//	sf::Sprite &getSnakeSprite(); --> Might be needed for collision check later

};

#endif