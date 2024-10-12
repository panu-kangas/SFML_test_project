#include "StartMenu.hpp"


/*
	CONSTRUCTOR
*/

StartMenu::StartMenu()
{
	selector = 0;

	buttonSize.x = 120;
	buttonSize.y = 50;

	startButtonPos.x = WINDOW_WIDTH / 2 - buttonSize.x / 2;
	startButtonPos.y = WINDOW_HEIGHT / 2;

	exitButtonPos.x = startButtonPos.x;
	exitButtonPos.y = startButtonPos.y + buttonSize.y;

	startButton.initTextBox("fonts/pixel_font.ttf", 28);
	startButton.setBackground(buttonSize, startButtonPos, sf::Color::Transparent);
	startButton.setText("START", sf::Vector2f(startButtonPos.x + 12, startButtonPos.y + 5), sf::Color::Green);

	exitButton.initTextBox("fonts/pixel_font.ttf", 28);
	exitButton.setBackground(buttonSize, exitButtonPos, sf::Color::Transparent);
	exitButton.setText("EXIT", sf::Vector2f(exitButtonPos.x + 27, exitButtonPos.y + 5), sf::Color::Green);

	std::ifstream	menufile("maps/startmenu.txt");

	if (!menufile.is_open())
	{
		std::cerr << RED << "\nStart menu error: could not open file.\n"
		<< "Exiting program.\n" << RESET << std::endl;
		exit (1);
	}

	std::string	tempStr;
	while (std::getline(menufile, tempStr))
	{
		for (char &c : tempStr)
			backgroundVec.push_back(c);
	}
}


/*
	BACKGROUND
*/

void	StartMenu::drawBackground(sf::RenderWindow &window, sf::Texture wall, sf::Texture grass)
{
	sf::Sprite	tempSprite;
	int			x = 0, y = 0;

	for (char &c : backgroundVec)
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



/*
	DRAW MENU
*/


void	StartMenu::drawMenu(sf::RenderWindow &window, sf::Texture wall, sf::Texture grass)
{
	drawBackground(window, wall, grass);
	startButton.drawTextBox(window);
	exitButton.drawTextBox(window);

	sf::RectangleShape	selectBorder;

	if (selector == 0)
		selectBorder.setPosition(startButtonPos);
	else if (selector == 1)
		selectBorder.setPosition(exitButtonPos);

	selectBorder.setSize(buttonSize);
	selectBorder.setFillColor(sf::Color::Transparent);
	selectBorder.setOutlineThickness(3);
	selectBorder.setOutlineColor(sf::Color::Black);
	window.draw(selectBorder);
}


/*
	SELECTOR HANDLING
*/

void	StartMenu::incrementSelector()
{
	if (selector < 1)
		selector++;
}

void	StartMenu::decrementSelector()
{
	if (selector > 0)
		selector--;
}


/*
	GETTERS
*/

int		StartMenu::getSelector()
{
	return (selector);
}

