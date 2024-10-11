#include "StartMenu.hpp"




/*
	BACKGROUND
*/

void	StartMenu::drawBackground(sf::RenderWindow &window, sf::Texture wall, sf::Texture grass)
{
	std::ifstream	menufile("maps/startmenu.txt");

	if (!menufile.is_open())
	{
		std::cerr << RED << "\nStart menu error: could not open file.\n"
		<< "Exiting program.\n" << RESET << std::endl;
		exit (1);
	}

	sf::Sprite	tempSprite;
	std::string	tempStr;
	int			x = 0, y = 0;

	while (std::getline(menufile, tempStr))
	{
		for (char &c : tempStr)
		{
			if (c == '1')
				tempSprite.setTexture(wall);
			else
				tempSprite.setTexture(grass);

			tempSprite.setPosition(x, y);
			x += TILE_SIZE;
			if (x == WINDOW_WIDTH)
			{
				y += TILE_SIZE;
				x = 0;
			}
			window.draw(tempSprite);
		}
	}
	
}
