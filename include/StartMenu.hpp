#ifndef STARTMENU_HPP
# define STARTMENU_HPP

# include <iostream>
# include <fstream>
# include <vector>
# include <SFML/Graphics.hpp>

# include "Constants.hpp"
# include "TextBox.hpp"

// TextBox class could have a name-attribute to identify boxes
// Then I could make these all just an array to loop over...

class StartMenu
{
	private:

	TextBox	startButton;
	TextBox	exitButton;
	TextBox level1Button;
	TextBox	level2Button;
	TextBox level3Button;
	TextBox backButton;

	std::vector<char>	backgroundVec;

	sf::Vector2f	buttonSize;
	sf::Vector2f	levelButtonSize;

	sf::Vector2f	startButtonPos;
	sf::Vector2f	exitButtonPos;
	sf::Vector2f	level1ButtonPos;
	sf::Vector2f	level2ButtonPos;
	sf::Vector2f	level3ButtonPos;
	sf::Vector2f	backButtonPos;

	int		selector; // 0 = start, 1 = exit
	bool	levelScreen;

	void	drawBackground(sf::RenderWindow &window, sf::Texture wall, sf::Texture grass);


	public:

	StartMenu();
	~StartMenu() {};

	void	initButtons();

	void	drawMenu(sf::RenderWindow &window, sf::Texture wall, sf::Texture grass);
	void	drawStartScreen(sf::RenderWindow &window);
	void	drawLevelScreen(sf::RenderWindow &window);

	void	incrementSelector();
	void	decrementSelector();

	void	setLevelScreenState(bool state);

	int		getSelector();
	void	resetSelector();

};

#endif