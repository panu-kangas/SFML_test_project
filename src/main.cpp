#include "Snake.hpp"

int main()
{
    auto window = sf::RenderWindow{ { 1000, 700 }, "SFML test" };
    window.setFramerateLimit(144); // check this later

	Snake snake;

	snake.Init(window);

    while (window.isOpen())
    {
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
		
		snake.moveSnake();
		snake.drawSnake(window);

        window.display();
    }
}
