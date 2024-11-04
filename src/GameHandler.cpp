#include "GameHandler.hpp"

/*
	CONSTRUCTOR
*/

GameHandler::GameHandler(sf::RenderWindow *gameWindow)
{
	window = gameWindow;
	gameState = StartScreen;
	spaceReleased = true;
	customMap = false;
}


/*
	INIT GAME
*/

void	GameHandler::initGame(std::string mapFile)
{
	map.initMap(mapFile);
	snake.initSnake(*window, map.getSnakeStartPos(), map.getMapWidth(), map.getMapHeight());
	
	score.initTextBox("fonts/pixel_font.ttf", 28);
	score.setBackground(sf::Vector2f(146, 32), sf::Vector2f(0, 0), sf::Color::Black);
	score.setCounter(map.getAppleCount());

	snakeInfoPos = snake.getSnakeSprite().getPosition();
	snakeInfoPos.x -= 90;
	snakeInfoPos.y -= 32;

	snakeStartInfo.initTextBox("fonts/pixel_font.ttf", 18);
	snakeStartInfo.setBackground(sf::Vector2f(230, 18), snakeInfoPos, sf::Color::Black);

	boostMeter.initTextBox("fonts/pixel_font.ttf", 14);
	boostMeter.setBackground(sf::Vector2f(160, 32), sf::Vector2f(WINDOW_WIDTH / 2 - 80, 0), sf::Color::Black);
	boostMeter.setText("BOOST METER", sf::Vector2f(WINDOW_WIDTH / 2 - 52, 0), sf::Color::White);

	endInfo.initTextBox("fonts/pixel_font.ttf", 14);
	endInfo.setBackground(sf::Vector2f(160, 32), sf::Vector2f(WINDOW_WIDTH - 160, 0), sf::Color::Black);
	endInfo.setText("Enter - Return to menu\nESC - Exit game", sf::Vector2f(WINDOW_WIDTH - 160, 0), sf::Color::Green);
}


/*
	UPDATE GAME
*/

void	GameHandler::updateGame(float dt)
{
	if (gameState == GameOver || gameState == Win)
		return ;
	else if (gameState == SnakeStill)
		snakeStartInfo.setText("Press W, A, S or D to start!", snakeInfoPos, sf::Color::Green);

	snake.moveSnake(map.getMapWidth(), map.getMapHeight(), dt); // Should I have map height & width in Handler as private...?

	for (int i = 0; i < arrowVec.size(); ++i)
	{
		arrowVec[i].moveArrow(dt);
		
		sf::Vector2f temp = arrowVec[i].getArrowTipCoord();
		temp.x /= TILE_SIZE;
		temp.y /= TILE_SIZE;

		if ((map.getTileInfo(temp.x, temp.y).type == '1'
		|| map.getTileInfo(temp.x, temp.y).type == 'T'
		|| map.getTileInfo(temp.x - 1, temp.y).type == 'T'
		|| map.getTileInfo(temp.x, temp.y - 1).type == 'T'
		|| map.getTileInfo(temp.x - 1, temp.y - 1).type == 'T')
		&& !arrowVec[i].getHomeTower().contains(arrowVec[i].getCoord()))
			arrowVec.erase(arrowVec.begin() + i);


		// check that the above erase() is safe!!		
	}
	
	if (snake.getStartMovingStatus() == true)
		gameState = SnakeMove;

	score.setText(score.getScoreString(), sf::Vector2f(80, 0), sf::Color::Green);

}


/*
	COLLISION CHECKING
*/

void	GameHandler::checkCollision()
{
	if (gameState == GameOver || gameState == Win)
		return ;

	int	tempFlag = map.checkCollisions(snake);

	if (tempFlag == 2)
	{
		if (score.decrementCounter() == true)
			gameState = Win;
		score.setText(score.getScoreString(), sf::Vector2f(80, 0), sf::Color::Green);
	}

	if (tempFlag == 0 || tempFlag == 2)
		tempFlag = checkArrowCollision();

	if (tempFlag == 1)
		gameState = GameOver;
	
}


int		GameHandler::checkArrowCollision()
{
	sf::Sprite &snakeSprite = snake.getSnakeSprite();
	std::vector<SnakeBody> &bodyVec = snake.getBodyVec();
	float snakeX = snake.getSnakeWorldCoord().x;
	float snakeY = snake.getSnakeWorldCoord().y;

	for (Arrow &arrow : arrowVec)
	{	
		if (arrow.getArrowTipCoord().x > snakeX && arrow.getArrowTipCoord().x < snakeX + TILE_SIZE \
		&& arrow.getArrowTipCoord().y > snakeY && arrow.getArrowTipCoord().y < snakeY + TILE_SIZE)
			return (1);
		
		for (SnakeBody &body : bodyVec)
		{
			if (arrow.getArrowTipCoord().x > body.getBodyCoord().x && arrow.getArrowTipCoord().x < body.getBodyCoord().x + TILE_SIZE \
			&& arrow.getArrowTipCoord().y > body.getBodyCoord().y && arrow.getArrowTipCoord().y < body.getBodyCoord().y + TILE_SIZE)
				return (1);
		}
	}

	return (0);
}


/*
	DRAW GAME
*/

void	GameHandler::drawGame(float dt)
{
	sf::Vector2f snakePos = snake.getSnakeWorldCoord();

	setXLimits(snakePos);
	setYLimits(snakePos);

	// MAP
	map.drawMap(*window, snake.getSnakeWorldCoord(), xDrawLimits, yDrawLimits, gameState);

	// TOWERS
	towerVec = map.getTowerVec();
	int	drawX, drawY;

	for (Tower &temp : *towerVec)
	{
		if (temp.isVisible(xDrawLimits, yDrawLimits) == true)
		{
			drawX =	temp.getPosInPixels().x - this->xDrawLimits[0];
			drawY = temp.getPosInPixels().y - this->yDrawLimits[0];
			temp.shootArrow(snakePos, arrowVec, snake.getStartMovingStatus(), gameState);

			// game over -screen coloring
			if (gameState == GameOver)
			{
				temp.getSprite().setColor(sf::Color::Red);
				temp.getWeaponSprite().setColor(sf::Color::Red);
			}
			temp.drawTower(*window, drawX, drawY, snake.getSnakeWorldCoord(), dt, gameState, map);
		}
		else
			temp.getSprite().setPosition(-100, -100); // is this needed...?
	}

	// ARROWS

	for (Arrow &temp : arrowVec)
	{
		drawX =	temp.getCoord().x - this->xDrawLimits[0];
		drawY = temp.getCoord().y - this->yDrawLimits[0];

		if (gameState == GameOver)
			temp.getSprite().setColor(sf::Color::Red);

		if (drawX > 0 && drawX < map.getMapWidth() * TILE_SIZE \
		&& drawY > 0 && drawY < map.getMapHeight() * TILE_SIZE)
			temp.drawArrow(*window, drawX, drawY);

	}
	
	// SNAKE
	snake.drawSnake(*window, gameState);

	// SCOREBOARD
	score.drawScore(*window);

	// Draw boost meter --> MAKE SEPARTE CLASS ???

	if (gameState == GameOver || gameState == Win)
	{
		if (gameState == GameOver)
			boostMeter.setText("GAME OVER", sf::Vector2f(WINDOW_WIDTH / 2 - 78, 0), sf::Color::Green);
		else
			boostMeter.setText("!! YOU WIN !!", sf::Vector2f(WINDOW_WIDTH / 2 - 71, 0), sf::Color::Green);
		boostMeter.setFontSize(25);
		boostMeter.drawTextBox(*window);
	}
	else
	{
		// BOOST METER BG
		boostMeter.drawTextBox(*window);

		sf::RectangleShape	boost;
		float				len;
		float				origLen = 100;

		len = snake.getBoostCounter();

		boost.setSize(sf::Vector2f(len, 10));
		boost.setFillColor(sf::Color::Green);
		boost.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - origLen / 2 + (origLen - len), 20));
		window->draw(boost);
	}



	if (gameState == SnakeStill)
		snakeStartInfo.drawTextBox(*window);
	else if (gameState == GameOver || gameState == Win)
		endInfo.drawTextBox(*window);

}

/*
	START MENU INPUT
*/

void	GameHandler::startMenuInput(sf::Event &event, char *argMap)
{
	if (event.type == sf::Event::KeyReleased)
		return ;

	if (event.key.scancode == sf::Keyboard::Scancode::W)
		startmenu.decrementSelector();
	else if (event.key.scancode == sf::Keyboard::Scancode::S)
		startmenu.incrementSelector();
	else if (event.key.code == sf::Keyboard::Key::Enter)
	{
		if (customMap == true && startmenu.getSelector() == 0)
		{
			initGame(argMap);
			gameState = SnakeStill;
		}
		else if (startmenu.getSelector() == 0)
		{
			gameState = LevelScreen;
			startmenu.setLevelScreenState(true);
		}
		else
		{
			std::cout << "\033[31m" 
			<< "\nThank you for playing! =)\n" << "\033[0m" << std::endl;
			exit (0);
		}
	}
}

void	GameHandler::levelScreenInput(sf::Event &event, GameHandler &game)
{
	if (event.type == sf::Event::KeyReleased)
		return ;

	if (event.key.scancode == sf::Keyboard::Scancode::W)
		startmenu.decrementSelector();
	else if (event.key.scancode == sf::Keyboard::Scancode::S)
		startmenu.incrementSelector();
	else if (event.key.code == sf::Keyboard::Key::Enter)
	{
		switch (startmenu.getSelector())
		{
			case 0:
				game.initGame("maps/level_1.txt");
				gameState = SnakeStill;
				break ;
			case 1:
				game.initGame("maps/level_2.txt");
				gameState = SnakeStill;
				break ;
			case 2:
				game.initGame("maps/level_3.txt");
				gameState = SnakeStill;
				break ;
			case 3:
				gameState = StartScreen;
				startmenu.setLevelScreenState(false);
				break ;
			default:
				break ;
		}
		
		startmenu.resetSelector();
		startmenu.setLevelScreenState(false);

	}
}


/*
	CHANGE SNAKE DIRECTION && BOOST
*/


void	GameHandler::checkInput(sf::Event &event)
{
	if (event.key.scancode == sf::Keyboard::Scan::Space)
	{
		if (event.type == sf::Event::KeyPressed && spaceReleased == true)
		{
			snake.setBoostStatus(true);
			spaceReleased = false;
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			snake.setBoostStatus(false);
			spaceReleased = true;
		}
	}
	else if (event.type == sf::Event::KeyPressed)
		snake.changeDirection(event);

}


/*
	RESET GAME
*/


void	GameHandler::resetGame()
{
	map.resetMap();
	snake.resetSnake(map.getSnakeStartPos(), map.getMapWidth(), map.getMapHeight());
	arrowVec.clear();

	boostMeter.setText("BOOST METER", sf::Vector2f(WINDOW_WIDTH / 2 - 52, 0), sf::Color::White);
	boostMeter.setFontSize(14);

	gameState = StartScreen;
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

void	GameHandler::setCustomMapState(int state)
{
	customMap = state;
}





