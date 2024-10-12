#ifndef STARTMENU_HPP
# define STARTMENU_HPP

# include <iostream>
# include <fstream>
# include <vector>
# include <SFML/Graphics.hpp>

# include "Constants.hpp"
# include "TextBox.hpp"

class StartMenu
{
	private:

	TextBox	startButton;
	TextBox	exitButton;

	std::vector<char>	backgroundVec;

	sf::Vector2f	buttonSize;
	sf::Vector2f	startButtonPos;
	sf::Vector2f	exitButtonPos;

	int		selector; // 0 = start, 1 = exit

	void	drawBackground(sf::RenderWindow &window, sf::Texture wall, sf::Texture grass);


	public:

	StartMenu();
	~StartMenu() {};

	void	drawMenu(sf::RenderWindow &window, sf::Texture wall, sf::Texture grass);

	void	incrementSelector();
	void	decrementSelector();

	int		getSelector();

};

#endif