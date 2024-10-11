#include "GameHandler.hpp"


int main(int argc, char *argv[])
{

	if (argc != 2)
	{
		std::cerr << RED << "\nInvalid amount of arguments; please provide one map-file as argument\n"
		<< RESET << std::endl;
		return (1);
	}


    auto window = sf::RenderWindow{ { WINDOW_WIDTH, WINDOW_HEIGHT }, "SFML test" };
    window.setFramerateLimit(60); // check this later



	GameHandler game(&window);
	game.initGame(argv[1]);



    while (window.isOpen())
    {

		if (game.getGameState() == 3)
		{
			std::cout << "\033[31m" << "\nYOU LOSE!\n" << "\033[0m" << std::endl;
			window.close();
			break ;
		}

        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
			else if (event.type == sf::Event::KeyPressed)
			{
				game.changeSnakeDir(event);

				if (event.key.scancode == sf::Keyboard::Scan::Escape)
					window.close(); // should I break ; here...?
			}
        }


        window.clear();


		if (game.getGameState() == 0)
		{
			game.displayStartMenu();
		}
		else
		{
			game.updateGame();
			game.checkCollision();
			game.drawGame();
		}

        window.display();
    }

	return (0);
}






// OLD VERSIONS



/*
	Class creation & initialization start
*/

/*
	int	state = 0; // JUST A TEST
	int collisionFlag;

	Map		map;
	map.initMap(argv[1]);

	Snake	snake;
	snake.Init(window, map.getSnakeStartPos(), map.getMapWidth(), map.getMapHeight());

	ScoreCounter score;
	score.initTextBox("fonts/pixel_font.ttf", 28);
	score.setBackground(sf::Vector2f(112, 32), sf::Vector2f(0, 0), sf::Color::Black);

	TextBox	snakeStartInfo;
	sf::Vector2f	snakeInfoPos = snake.getSnakeSprite().getPosition();

	snakeInfoPos.x -= 90;
	snakeInfoPos.y -= 32;

	snakeStartInfo.initTextBox("fonts/pixel_font.ttf", 18);
	snakeStartInfo.setBackground(sf::Vector2f(230, 18), snakeInfoPos, sf::Color::Black);	

	*/

/*
	Class creation & initialization end
*/



//	map.drawMap(window, snake);

	//	snake.moveSnake(map.getMapWidth(), map.getMapHeight());
	//	snake.drawSnake(window);

	//	score.setText(score.getScoreString(), sf::Vector2f(10, 0), sf::Color::Green);
	//	score.drawText(window);

	/*	if (snake.getStartMovingStatus() == false)
		{
			snakeStartInfo.setText("Press W, A, S or D to start!", snakeInfoPos, sf::Color::Green);
			snakeStartInfo.drawText(window);
		}
*/


/*	collisionFlag = map.checkCollisions(snake);

		if (collisionFlag == 1)
			state = 1;
		else if (collisionFlag == 2)
			score.addScore(100);
*/