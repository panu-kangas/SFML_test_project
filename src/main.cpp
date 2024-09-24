#include "Snake.hpp"
#include "Map.hpp"
#include "ScoreCounter.hpp"

/*
sf::Vector2f makeVector2f(float x, float y)
{
	sf::Vector2f temp;

	temp.x = x;
	temp.y = y;

	return (temp);
}
*/


int main(int argc, char *argv[])
{

	if (argc != 2)
	{
		std::cerr << RED << "\nInvalid amount of arguments; please provide one map-file as argument\n"
		<< RESET << std::endl;
		return (1);
	}

    auto window = sf::RenderWindow{ { WINDOW_WIDTH, WINDOW_HEIGHT }, "SFML test" };
    window.setFramerateLimit(144); // check this later

	int	state = 0; // JUST A TEST
	int collisionFlag;

	Map		map;
	map.initMap(argv[1]);

	Snake	snake;
	snake.Init(window, map.getSnakeStartPos());

	ScoreCounter score;
	score.initTextBox("fonts/pixel_font.ttf", 28);
	score.setBackground(sf::Vector2f(112, 32), sf::Vector2f(0, 0), sf::Color::Black);



    while (window.isOpen())
    {
		if (state == 1)
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
				snake.changeDirection(event);

				if (event.key.scancode == sf::Keyboard::Scan::Escape)
					window.close(); // should I break ; here...?
			}
        }


        window.clear();
		
		map.drawMap(window);

		snake.moveSnake();
		snake.drawSnake(window);

		score.setText(score.getScoreString(), sf::Vector2f(10, 0), sf::Color::Green);
		score.drawText(window);

		collisionFlag = map.checkCollisions(snake);

		if (collisionFlag == 1)
			state = 1;
		else if (collisionFlag == 2)
			score.addScore(100);

        window.display();
    }
}
