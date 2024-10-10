#ifndef GAMEHANDLER_HPP
# define GAMEHANDLER_HPP

# include <iostream>
# include <vector>
# include <SFML/Graphics.hpp>

# include "Constants.hpp"
# include "Map.hpp"
# include "ScoreCounter.hpp"
# include "Snake.hpp"
# include "Tower.hpp"


class GameHandler
{
	private:

	Map				map;
	Snake			snake;
	ScoreCounter	score;
	TextBox			snakeStartInfo;

	sf::RenderWindow	*window;

	sf::Vector2f		snakeInfoPos;

//	std::vector<Tower>	towerVec; --> GET THIS FROM MAP

	// 0 = start screen (NOT DONE), 1 = snake still, 2 = start, 3 = game over
	int		gameState;


	public:

	// Should I have a default constructor here...?
	GameHandler(sf::RenderWindow *gameWindow);
	~GameHandler() {};

	void	initGame(std::string mapFile);
	void	updateGame();
	void	checkCollision();
	void	drawGame();


	void	changeSnakeDir(sf::Event event);


	int		getGameState();

	void	setGameState(int state);

};

#endif