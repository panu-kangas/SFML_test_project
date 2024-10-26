#include "ScoreCounter.hpp"


ScoreCounter::ScoreCounter()
{
	info.initTextBox("fonts/pixel_font.ttf", 14);
	info.setBackground(sf::Vector2f(112, 32), sf::Vector2f(0, 0), sf::Color::Transparent);
	info.setText("APPLES\nLEFT:", {10, 0}, sf::Color::White);

}



std::string	ScoreCounter::getScoreString()
{
	return (std::to_string(appleCount));
}

bool	ScoreCounter::decrementCounter()
{
	appleCount--;

	if (appleCount == 0)
		return (true);
	else
		return (false);
}

void	ScoreCounter::setCounter(int appleTotal)
{
	appleCount = appleTotal;
}

void	ScoreCounter::drawScore(sf::RenderWindow &window)
{
	this->drawTextBox(window);
	info.drawTextBox(window);
}

