#include "StartMenu.hpp"


/*
	CONSTRUCTOR
*/

StartMenu::StartMenu()
{
	selector = 0;
	levelScreen = false;

	initButtons();

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

void	StartMenu::initButtons()
{
	buttonSize.x = 120;
	buttonSize.y = 50;

	levelButtonSize.x = 150;
	levelButtonSize.y = 50;


	// TextBox class could have a name-attribute to identify boxes
	// Then I could make these all just an array to loop over...

	startButtonPos.x = WINDOW_WIDTH / 2 - buttonSize.x / 2;
	startButtonPos.y = WINDOW_HEIGHT / 2;

	exitButtonPos.x = startButtonPos.x;
	exitButtonPos.y = startButtonPos.y + buttonSize.y;

	level1ButtonPos.x = WINDOW_WIDTH / 2 - levelButtonSize.x / 2;
	level1ButtonPos.y = WINDOW_HEIGHT / 2;

	level2ButtonPos.x = level1ButtonPos.x;
	level2ButtonPos.y = level1ButtonPos.y + buttonSize.y;

	level3ButtonPos.x = level2ButtonPos.x;
	level3ButtonPos.y = level2ButtonPos.y + buttonSize.y;

	backButtonPos.x = level3ButtonPos.x;
	backButtonPos.y = level3ButtonPos.y + buttonSize.y;

	startButton.initTextBox("fonts/pixel_font.ttf", 28);
	startButton.setBackground(buttonSize, startButtonPos, sf::Color::Transparent);
	startButton.setText("START", sf::Vector2f(startButtonPos.x + 12, startButtonPos.y + 5), sf::Color::Green);

	exitButton.initTextBox("fonts/pixel_font.ttf", 28);
	exitButton.setBackground(buttonSize, exitButtonPos, sf::Color::Transparent);
	exitButton.setText("EXIT", sf::Vector2f(exitButtonPos.x + 27, exitButtonPos.y + 5), sf::Color::Green);

	level1Button.initTextBox("fonts/pixel_font.ttf", 28);
	level1Button.setBackground(levelButtonSize, level1ButtonPos, sf::Color::Transparent);
	level1Button.setText("LEVEL 1", sf::Vector2f(level1ButtonPos.x + 20, level1ButtonPos.y + 5), sf::Color::Green);

	level2Button.initTextBox("fonts/pixel_font.ttf", 28);
	level2Button.setBackground(levelButtonSize, level2ButtonPos, sf::Color::Transparent);
	level2Button.setText("LEVEL 2", sf::Vector2f(level2ButtonPos.x + 20, level2ButtonPos.y + 5), sf::Color::Green);

	level3Button.initTextBox("fonts/pixel_font.ttf", 28);
	level3Button.setBackground(levelButtonSize, level3ButtonPos, sf::Color::Transparent);
	level3Button.setText("LEVEL 3", sf::Vector2f(level3ButtonPos.x + 20, level3ButtonPos.y + 5), sf::Color::Green);

	backButton.initTextBox("fonts/pixel_font.ttf", 28);
	backButton.setBackground(buttonSize, backButtonPos, sf::Color::Transparent);
	backButton.setText("RETURN", sf::Vector2f(backButtonPos.x + 16, backButtonPos.y + 5), sf::Color::Green);
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

	if (levelScreen == false)
		drawStartScreen(window);
	else
		drawLevelScreen(window);

}


void	StartMenu::drawStartScreen(sf::RenderWindow &window)
{
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

void	StartMenu::drawLevelScreen(sf::RenderWindow &window)
{
	level1Button.drawTextBox(window);
	level2Button.drawTextBox(window);
	level3Button.drawTextBox(window);
	backButton.drawTextBox(window);

	sf::RectangleShape	selectBorder;

	switch (selector)
	{
		case 0:
			selectBorder.setPosition(level1ButtonPos);
			break ;
		case 1:
			selectBorder.setPosition(level2ButtonPos);
			break ;
		case 2:
			selectBorder.setPosition(level3ButtonPos);
			break ;
		case 3:
			selectBorder.setPosition(backButtonPos);
			break ;
		default:
			break ;
	}

	selectBorder.setSize(levelButtonSize);
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
	if ((levelScreen == false && selector < 1) \
	|| (levelScreen == true && selector < 3))
		selector++;
}

void	StartMenu::decrementSelector()
{
	if (selector > 0)
		selector--;
}


/*
	SETTERS
*/

void	StartMenu::setLevelScreenState(bool state)
{
	levelScreen = state;
}


/*
	GETTERS
*/

int		StartMenu::getSelector()
{
	return (selector);
}

void	StartMenu::resetSelector()
{
	selector = 0;
}


