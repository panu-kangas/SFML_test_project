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

	sf::Clock	deltaClock;



    while (window.isOpen())
    {
	
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
                window.close();
			else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
			{
				if (game.getGameState() == StartScreen) // how to get enum here...? Use global enum?
					game.startMenuInput(event);
				else if (game.getGameState() == GameOver && event.key.scancode == sf::Keyboard::Scan::Enter)
					game.resetGame();
				else
					game.checkInput(event);

				if (event.key.scancode == sf::Keyboard::Scan::Escape)
					window.close(); // should I break ; here...?
			}
        }

		sf::Time dt = deltaClock.restart();


       	window.clear();

		if (game.getGameState() == StartScreen)
			game.displayStartMenu();
		else
		{
			game.updateGame(dt.asSeconds());
			game.checkCollision();
			game.drawGame(dt.asSeconds());
		}

       	window.display();

    }

	return (0);
}


