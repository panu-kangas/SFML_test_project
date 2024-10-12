#include "GameHandler.hpp"

/*
	CONSTRUCTOR
*/

GameHandler::GameHandler(sf::RenderWindow *gameWindow)
{
	window = gameWindow;
	gameState = 0;
}


/*
	INIT GAME
*/

void	GameHandler::initGame(std::string mapFile)
{
	map.initMap(mapFile);
	snake.initSnake(*window, map.getSnakeStartPos(), map.getMapWidth(), map.getMapHeight());
	
	score.initTextBox("fonts/pixel_font.ttf", 28);
	score.setBackground(sf::Vector2f(112, 32), sf::Vector2f(0, 0), sf::Color::Black);

	snakeInfoPos = snake.getSnakeSprite().getPosition();
	snakeInfoPos.x -= 90;
	snakeInfoPos.y -= 32;

	snakeStartInfo.initTextBox("fonts/pixel_font.ttf", 18);
	snakeStartInfo.setBackground(sf::Vector2f(230, 18), snakeInfoPos, sf::Color::Black);
}


/*
	UPDATE GAME
*/

void	GameHandler::updateGame()
{
	if (gameState == 1)
		snakeStartInfo.setText("Press W, A, S or D to start!", snakeInfoPos, sf::Color::Green);

	snake.moveSnake(map.getMapWidth(), map.getMapHeight()); // Should I have map height & width in Handler as private...?

	for (int i = 0; i < arrowVec.size(); ++i)
	{
		arrowVec[i].moveArrow();
		
		sf::Vector2f temp = arrowVec[i].getCoord();

		if (temp.x < 0 || temp.x > map.getMapWidth() * TILE_SIZE \
		|| temp.y < 0 || temp.y > map.getMapHeight() * TILE_SIZE)
			arrowVec.erase(arrowVec.begin() + i);

		// check that the above erase() is safe!!		
	}
	
	if (snake.getStartMovingStatus() == true)
		gameState = 2;

	score.setText(score.getScoreString(), sf::Vector2f(10, 0), sf::Color::Green);

}


/*
	COLLISION CHECKING
*/

void	GameHandler::checkCollision()
{
	int	tempFlag = map.checkCollisions(snake);

	if (tempFlag == 1)
		gameState = 3;
	else if (tempFlag == 2)
		score.addScore(100);

}

/*
	DRAW GAME
*/

void	GameHandler::drawGame()
{
	sf::Vector2f snakePos = snake.getSnakeWorldCoord();

	setXLimits(snakePos);
	setYLimits(snakePos);

	// MAP
	map.drawMap(*window, snake.getSnakeWorldCoord(), xDrawLimits, yDrawLimits);

	// TOWERS
	towerVec = map.getTowerVec();
	int	drawX, drawY;

	for (Tower &temp : *towerVec)
	{
		if (temp.isVisible(xDrawLimits, yDrawLimits) == true)
		{
				drawX =	temp.getPosInPixels().x - this->xDrawLimits[0];
				drawY = temp.getPosInPixels().y - this->yDrawLimits[0];
				temp.shootArrow(snakePos, arrowVec);
				temp.drawTower(*window, drawX, drawY, snake.getSnakeWorldCoord());
		}
		else
			temp.getSprite().setPosition(-10, -10); // is this needed...?
	}

	// ARROWS

	for (Arrow &temp : arrowVec) // do i need to check if it's empty...?
	{
		drawX =	temp.getCoord().x - this->xDrawLimits[0];
		drawY = temp.getCoord().y - this->yDrawLimits[0];

		if (drawX > 0 && drawX < map.getMapWidth() * TILE_SIZE \
		&& drawY > 0 && drawY < map.getMapHeight() * TILE_SIZE)
			temp.drawArrow(*window, drawX, drawY);
	}
	

	// SNAKE
	snake.drawSnake(*window);

	// SCOREBOARD
	score.drawTextBox(*window);

	if (gameState == 1)
		snakeStartInfo.drawTextBox(*window);

}

/*
	START MENU INPUT
*/

void	GameHandler::startMenuInput(sf::Event &event)
{
	if (event.key.code == sf::Keyboard::Key::Up) // scancode vs key ???
		startmenu.decrementSelector();
	else if (event.key.code == sf::Keyboard::Key::Down) // scancode vs key ???
		startmenu.incrementSelector();
	else if (event.key.code == sf::Keyboard::Key::Enter)
	{
		if (startmenu.getSelector() == 0)
			gameState = 1;
		else
		{
			std::cout << "\033[31m" 
			<< "\nWell... you could have at least tried the game! =(\n" << "\033[0m" << std::endl;
			exit (0);
		}
	}
}


/*
	CHANGE SNAKE DIRECTION
*/

void	GameHandler::changeSnakeDir(sf::Event &event)
{
	snake.changeDirection(event);
}


/*
	SET DRAW LIMITS
*/


void	GameHandler::setXLimits(sf::Vector2f snakePos)
{
	// Should the multiplier (16) be universal and counted base on window size...?
	// Now, if window size changes, the drawing doesn't work!

	int mapWidth = map.getMapWidth();

	xDrawLimits[0] = (snakePos.x) - (16 * TILE_SIZE);
	xDrawLimits[1] = (snakePos.x) + (16 * TILE_SIZE) + TILE_SIZE;

	if (xDrawLimits[0] <= 0)
	{
		xDrawLimits[0] = 0;
		xDrawLimits[1] = WINDOW_WIDTH;
		return ;
	}
	else if (xDrawLimits[1] >= mapWidth * TILE_SIZE)
	{
		xDrawLimits[0] = (mapWidth * TILE_SIZE) - (WINDOW_WIDTH);
		xDrawLimits[1] = mapWidth * TILE_SIZE;
	}

	// Adding the off-screen part of first tile to the last drawn tile.
	// This way, full screen gets drawn.

	if (xDrawLimits[0] % TILE_SIZE != 0)
		xDrawLimits[1] += TILE_SIZE - (xDrawLimits[0] % TILE_SIZE);


}

void	GameHandler::setYLimits(sf::Vector2f snakePos)
{
	// Should the multiplier (11) be universal and counted base on window size...?
	// Now, if window size changes, the drawing doesn't work!

	int mapHeight = map.getMapHeight();

	yDrawLimits[0] = (snakePos.y) - (11 * TILE_SIZE);
	yDrawLimits[1] = (snakePos.y) + (11 * TILE_SIZE) + TILE_SIZE;

	if (yDrawLimits[0] <= 0)
	{
		yDrawLimits[0] = 0;
		yDrawLimits[1] = WINDOW_HEIGHT;
		return ;
	}
	else if (yDrawLimits[1] >= mapHeight * TILE_SIZE)
	{
		yDrawLimits[0] = (mapHeight * TILE_SIZE) - WINDOW_HEIGHT;
		yDrawLimits[1] = mapHeight * TILE_SIZE;
	}

	// Adding the off-screen part of first tile to the last drawn tile.
	// This way, full screen gets drawn.

	if (yDrawLimits[0] % TILE_SIZE != 0)
		yDrawLimits[1] += TILE_SIZE - (yDrawLimits[0] % TILE_SIZE);


}


/*
	MENU
*/

void	GameHandler::displayStartMenu()
{
	startmenu.drawMenu(*window, map.getWallTexture(), map.getGrassTexture());
}




/*
	GETTERS
*/


int		GameHandler::getGameState()
{
	return (gameState);
}


/*
	SETTERS
*/

void	GameHandler::setGameState(int state)
{
	gameState = state;
}


