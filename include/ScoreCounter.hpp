#ifndef SCORECOUNTER_HPP
# define SCORECOUNTER_HPP

# include "TextBox.hpp"

class ScoreCounter : public TextBox
{
	private:

	int			appleCount;
	TextBox		info;

	public:

	ScoreCounter();
	~ScoreCounter() {};

	std::string	getScoreString();

	bool	decrementCounter();
	void	setCounter(int appleTotal);

	void	drawScore(sf::RenderWindow &window);

};

#endif