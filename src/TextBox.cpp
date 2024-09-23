#include "TextBox.hpp"

// Functionalities

void	TextBox::initTextBox(std::string path_to_font, unsigned int size)
{
	if (!this->boxFont.loadFromFile(path_to_font))
	{
		std::cerr << RED << "Font loading failed. Exiting program!" << RESET << std::endl;
		exit (1);
	}

	this->textSize = size;
}

void	TextBox::setBackground(sf::Vector2f size, sf::Vector2f position, sf::Color color)
{
	this->boxBackground.setSize(size);
	this->boxBackground.setPosition(position);
	this->boxBackground.setFillColor(color);
}


void	TextBox::setText(std::string text, sf::Vector2f position, sf::Color color)
{
	this->boxText.setFont(this->boxFont);
	this->boxText.setString(text);
	this->boxText.setCharacterSize(this->textSize);
	this->boxText.setFillColor(color);
	this->boxText.setPosition(position.x, position.y);
}

void	TextBox::drawText(sf::RenderWindow &window)
{
	window.draw(this->boxBackground);
	window.draw(this->boxText);
}

