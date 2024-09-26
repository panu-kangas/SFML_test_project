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
	int			moveStartCounter;

	sf::Vector2f	bodyWorldCoord; // in pixels!

	std::vector<int> 			newDirVec;
	std::vector<sf::Vector2f>	turnPointVec;


	public:

	SnakeBody();
	~SnakeBody() {};

	void	InitBody(sf::RenderWindow &window, sf::Texture &bodyText, sf::Vector2i startPos, int num);
	void	drawSnakeBody(sf::RenderWindow &window);
	void	moveSnakeBody(int mapWidth, int mapHeight, sf::Vector2f snakeHeadPos);

	void	addTurn(int direction, sf::Vector2f turnPoint);
	void	setNextBody(SnakeBody *next);

//	sf::Sprite &getSnakeSprite(); --> Might be needed for collision check later

};

#endif