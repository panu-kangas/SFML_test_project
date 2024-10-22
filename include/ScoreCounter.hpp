#ifndef SCORECOUNTER_HPP
# define SCORECOUNTER_HPP

# include "TextBox.hpp"

class ScoreCounter : public TextBox
{
	private:

	int	score;

	public:

	ScoreCounter() : score(0) {};
	~ScoreCounter() {};

	std::string	getScoreString();

	void	addScore(int add);
	void	resetScore();

};

#endif