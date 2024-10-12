#ifndef TEXTBOX_HPP
# define TEXTBOX_HPP

# include <iostream>
# include <SFML/Graphics.hpp>

# include "Constants.hpp"

class TextBox
{
	private:

	sf::Font	boxFont;
	sf::Text	boxText;
	sf::RectangleShape	boxBackground;

	unsigned int	textSize;

	public:

	TextBox() {};
	virtual ~TextBox() {};

	void	initTextBox(std::string path_to_font, unsigned int size);

	void	setBackground(sf::Vector2f size, sf::Vector2f position, sf::Color color);
	void	setText(std::string text, sf::Vector2f position, sf::Color color);
	void	drawTextBox(sf::RenderWindow &window);

};

#endif