#include "ScoreCounter.hpp"

std::string	ScoreCounter::getScoreString()
{
	return (std::to_string(this->score));
}

void	ScoreCounter::addScore(int add)
{
	this->score += add;
}

void	ScoreCounter::resetScore()
{
	score = 0;
}
