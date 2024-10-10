#include "GameHandler.hpp"

/*
	CONSTRUCTOR
*/

// is this needed here...?

GameHandler::GameHandler(sf::RenderWindow *gameWindow)
{
	this->window = gameWindow;
	this->gameState = 1;
}


/*
	INIT GAME
*/

void	GameHandler::initGame(std::string mapFile)
{
	this->map.initMap(mapFile);
	this->snake.initSnake(*this->window, this->map.getSnakeStartPos(), this->map.getMapWidth(), this->map.getMapHeight());
	
	this->score.initTextBox("fonts/pixel_font.ttf", 28);
	this->score.setBackground(sf::Vector2f(112, 32), sf::Vector2f(0, 0), sf::Color::Black);

	this->snakeInfoPos = snake.getSnakeSprite().getPosition();
	this->snakeInfoPos.x -= 90;
	this->snakeInfoPos.y -= 32;

	this->snakeStartInfo.initTextBox("fonts/pixel_font.ttf", 18);
	this->snakeStartInfo.setBackground(sf::Vector2f(230, 18), snakeInfoPos, sf::Color::Black);
}


/*
	UPDATE GAME
*/

void	GameHandler::updateGame()
{
	if (this->gameState == 1)
		snakeStartInfo.setText("Press W, A, S or D to start!", this->snakeInfoPos, sf::Color::Green);

	this->map.drawMap(*this->window, this->snake);
	this->snake.moveSnake(this->map.getMapWidth(), this->map.getMapHeight()); // Should I have map height & width in Handler as private...?

	if (this->snake.getStartMovingStatus() == true)
		this->gameState = 2;

	this->score.setText(this->score.getScoreString(), sf::Vector2f(10, 0), sf::Color::Green);


}


/*
	COLLISION CHECKING
*/

void	GameHandler::checkCollision()
{
	int	collisionFlag = this->map.checkCollisions(this->snake);

	if (collisionFlag == 1)
		this->gameState = 3;
	else if (collisionFlag == 2)
		this->score.addScore(100);

}

/*
	DRAW GAME
*/

void	GameHandler::drawGame()
{
	this->snake.drawSnake(*this->window);
	this->score.drawText(*this->window);

	if (this->gameState == 1)
		snakeStartInfo.drawText(*this->window);


}




/*
	CHANGE DIRECTION
*/

void	GameHandler::changeSnakeDir(sf::Event event)
{
	this->snake.changeDirection(event);
}




/*
	GETTERS
*/


int		GameHandler::getGameState()
{
	return (this->gameState);
}


/*
	SETTERS
*/

void	GameHandler::setGameState(int state)
{
	this->gameState = state;
}


