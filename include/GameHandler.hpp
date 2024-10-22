#ifndef GAMEHANDLER_HPP
# define GAMEHANDLER_HPP

# include <iostream>
# include <vector>
# include <SFML/Graphics.hpp>

# include "Constants.hpp"
# include "Map.hpp"
# include "ScoreCounter.hpp"
# include "StartMenu.hpp"
# include "Snake.hpp"
# include "Tower.hpp"
# include "Arrow.hpp"


class GameHandler
{
	private:

	Map				map;
	Snake			snake;
	ScoreCounter	score;
	StartMenu		startmenu;
	TextBox			snakeStartInfo;
	TextBox			boostMeter;

	sf::RenderWindow	*window;

	sf::Vector2f		snakeInfoPos;

	std::vector<Tower>	*towerVec; // I should probably have this vec only here, not in the map!
	std::vector<Arrow>	arrowVec;


	int			gameState;

	bool		spaceReleased;



	int		xDrawLimits[2]; // in pixels!
	int		yDrawLimits[2]; // in pixels!

	// Private functions

	void	setXLimits(sf::Vector2f snakePos);
	void	setYLimits(sf::Vector2f snakePos);
	int		checkArrowCollision();



	public:

	// Should I have a default constructor here...?
	GameHandler(sf::RenderWindow *gameWindow);
	~GameHandler() {};

	void	initGame(std::string mapFile);
	void	updateGame(float dt);
	void	checkCollision();
	void	drawGame(float dt);

	void	displayStartMenu();
	void	startMenuInput(sf::Event &event);

	void	resetGame();

	void	checkInput(sf::Event &event);


	int		getGameState();

	void	setGameState(int state);
//	void	setSpaceState(bool state);

};

#endif