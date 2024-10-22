#ifndef SNAKE_HPP
# define SNAKE_HPP

# include <iostream>
# include <vector>
# include <SFML/Graphics.hpp>

# include "Constants.hpp"
# include "SnakeBody.hpp"


class Snake
{
	private:

	sf::Texture	snakeHeadTexture;
	sf::Sprite	snakeHeadSprite;

	sf::Texture				bodyTexture;
	std::vector<SnakeBody>	bodyVec;
	int						bodyCount;

	bool		startMoving;
	bool		isBoosting;
	bool		bodyReady;

	int			curDirection; // 0 up, 1 right, 2 down, 3 left
	int			newDirection;
	int			moveSpeed;
	float		boostCounter;

	sf::Vector2f	snakeWorldCoord; // in pixels!

	void	setSpritePosition(int mapWidth, int mapHeight);
	void	checkBoost(float dt);


	public:

	Snake();
	~Snake() {};

	void	initSnake(sf::RenderWindow &window, sf::Vector2f startPos, int mapWidth, int mapHeight);
	void	drawSnake(sf::RenderWindow &window, int gameState);
	void	moveSnake(int mapWidth, int mapHeight, float dt);
	void	changeDirection(sf::Event &keypress);

	void		resetSnake(sf::Vector2f startPos, int mapWidth, int mapHeight);


	void		setSpeed(int newSpeed);
	void		setBoostStatus(bool status);

	int						getMoveSpeed();
	sf::Sprite				&getSnakeSprite();
	sf::Vector2f			getSnakeWorldCoord();
	std::vector<SnakeBody>	&getBodyVec();
	bool					getStartMovingStatus();
	bool					getBoostStatus();
	float					getBoostCounter();
};

#endif