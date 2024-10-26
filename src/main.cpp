#include "GameHandler.hpp"


int main(int argc, char *argv[])
{

	if (argc > 2)
	{
		std::cerr << RED << "\nToo many maps provided!\n"
		<< RESET << std::endl;
		return (1);
	}

    auto window = sf::RenderWindow{ { WINDOW_WIDTH, WINDOW_HEIGHT }, "Snake Adventures" };
    window.setFramerateLimit(144);


	GameHandler game(&window);

	if (argc == 2)
		game.setCustomMapState(true);

	sf::Clock	deltaClock;


    while (window.isOpen())
    {
		int curState = game.getGameState();

        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
                window.close();
			else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
			{
				if (curState == StartScreen) // how to get enum here...? Use global enum?
					game.startMenuInput(event, argv[1]);
				else if (curState == LevelScreen)
					game.levelScreenInput(event, game);
				else if ((curState == GameOver || curState == Win) && event.key.scancode == sf::Keyboard::Scan::Enter)
					game.resetGame();
				else
					game.checkInput(event);

				if (event.key.scancode == sf::Keyboard::Scan::Escape)
					window.close(); // should I break ; here...?
			}
        }

		sf::Time dt = deltaClock.restart();

       	window.clear();

		if (game.getGameState() == StartScreen || game.getGameState() == LevelScreen)
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


