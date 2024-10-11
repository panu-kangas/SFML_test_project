#ifndef STARTMENU_HPP
# define STARTMENU_HPP

# include <iostream>
# include <fstream>
# include <SFML/Graphics.hpp>

# include "Constants.hpp"

class StartMenu
{
	private:



	public:

	StartMenu() {};
	~StartMenu() {};

	void	drawBackground(sf::RenderWindow &window, sf::Texture wall, sf::Texture grass);

};

#endif