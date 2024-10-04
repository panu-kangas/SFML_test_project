#ifndef TOWER_HPP
# define TOWER_HPP


# include <iostream>
# include <vector>
# include <SFML/Graphics.hpp>

# include "Constants.hpp"

class Tower
{
	private:

	sf::Sprite		towerSprite;
	sf::Sprite		weaponSprite;

	sf::Vector2f	towerCoord; // Tile coordinates, NOT pixels!!

	sf::Clock		towerClock;

	int				weaponAngle;
	int				weaponIdleAngle;
	int				idleAngleIncrement;

	int				attackRadius;


	public:

	Tower(sf::Texture &towerText, sf::Texture &weaponText, sf::Vector2f towerCoord);
	~Tower() {};

	void	drawTower(sf::RenderWindow &window);
	bool	isVisible(int *xDrawLimits, int *yDrawLimits);
	bool	isSnakeVisible(sf::Vector2f snakeWorldCoord);

	void	setAngle(int newAngle);
	void	setIdleAngle();
	void	setAttackAngle(sf::Vector2f snakePos);

	sf::Vector2f	getPosInPixels();
	sf::Sprite		&getSprite();
	sf::Sprite		&getWeaponSprite();
	int				&getWeaponAngle();

};


#endif