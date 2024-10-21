#include "GameHandler.hpp"

/*
	CONSTRUCTOR
*/

GameHandler::GameHandler(sf::RenderWindow *gameWindow)
{
	window = gameWindow;
	gameState = StartMenu;
	spaceReleased = true;
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

	boostMeter.initTextBox("fonts/pixel_font.ttf", 18);
	boostMeter.setBackground(sf::Vector2f(160, 32), sf::Vector2f(WINDOW_WIDTH / 2 - 80, 0), sf::Color::Black);
}


/*
	UPDATE GAME
*/

void	GameHandler::updateGame(float dt)
{
	if (gameState == SnakeStill)
		snakeStartInfo.setText("Press W, A, S or D to start!", snakeInfoPos, sf::Color::Green);

	snake.moveSnake(map.getMapWidth(), map.getMapHeight(), dt); // Should I have map height & width in Handler as private...?

	for (int i = 0; i < arrowVec.size(); ++i)
	{
		arrowVec[i].moveArrow(dt);
		
		sf::Vector2f temp = arrowVec[i].getArrowTipCoord();
		temp.x /= TILE_SIZE;
		temp.y /= TILE_SIZE;

		if (map.getTileInfo(temp.x, temp.y).type == '1')
			arrowVec.erase(arrowVec.begin() + i);

		/*
		Tried this to the if condition above:

		|| map.getTileInfo(temp.x, temp.y).type == 'T'
		|| map.getTileInfo(temp.x - 1, temp.y).type == 'T'
		|| map.getTileInfo(temp.x, temp.y - 1).type == 'T'
		|| map.getTileInfo(temp.x - 1, temp.y - 1).type == 'T'

		It almost works, just need to somehow skip the "home tower", so that the arrow
		doesn't stop immidiately :D
		*/


		// check that the above erase() is safe!!		
	}
	
	if (snake.getStartMovingStatus() == true)
		gameState = SnakeMove;

	score.setText(score.getScoreString(), sf::Vector2f(10, 0), sf::Color::Green);

}


/*
	COLLISION CHECKING
*/

void	GameHandler::checkCollision()
{
	int	tempFlag = map.checkCollisions(snake);

	if (tempFlag == 2)
		score.addScore(100);

	if (tempFlag == 0 || tempFlag == 2)
		tempFlag = checkArrowCollision();

	if (tempFlag == 1)
		gameState = GameOver;
	

}


int		GameHandler::checkArrowCollision()
{
	sf::Sprite &snakeSprite = snake.getSnakeSprite();
	std::vector<SnakeBody> &bodyVec = snake.getBodyVec();

	for (Arrow &temp : arrowVec)
	{
		if (temp.getSprite().getGlobalBounds().intersects(snakeSprite.getGlobalBounds()))
			return (1);
		
		for (SnakeBody &tempBody : bodyVec)
		{
			if (temp.getSprite().getGlobalBounds().intersects(tempBody.getSprite().getGlobalBounds()))
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
				temp.shootArrow(snakePos, arrowVec, snake.getStartMovingStatus());
				temp.drawTower(*window, drawX, drawY, snake.getSnakeWorldCoord(), dt);
		}
		else
			temp.getSprite().setPosition(-10, -10); // is this needed...?
	}

	// ARROWS

	for (Arrow &temp : arrowVec)
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

	// BOOST METER BG
	boostMeter.drawTextBox(*window);

	// Draw boost meter --> MAKE SEPARTE CLASS

	sf::RectangleShape	boost;
	float				len;
	float				origLen = 100;

	len = snake.getBoostCounter();

	boost.setSize(sf::Vector2f(len, 10));
	boost.setFillColor(sf::Color::Green);
	boost.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - origLen / 2 + (origLen - len), 10));
	window->draw(boost);


	if (gameState == SnakeStill)
		snakeStartInfo.drawTextBox(*window);

}

/*
	START MENU INPUT
*/

void	GameHandler::startMenuInput(sf::Event &event)
{
	if (event.type == sf::Event::KeyReleased)
		return ;

	if (event.key.code == sf::Keyboard::Key::Up) // scancode vs key ???
		startmenu.decrementSelector();
	else if (event.key.code == sf::Keyboard::Key::Down) // scancode vs key ???
		startmenu.incrementSelector();
	else if (event.key.code == sf::Keyboard::Key::Enter)
	{
		if (startmenu.getSelector() == 0)
			gameState = SnakeStill;
		else
		{
			std::cout << "\033[31m" 
			<< "\nWell... you could have at least tried the game! =(\n" << "\033[0m" << std::endl;
			exit (0);
		}
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




