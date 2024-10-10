#ifndef TOWER_HPP
# define TOWER_HPP

# include <iostream>
# include <vector>
# include <SFML/Graphics.hpp>

# include "Constants.hpp"


struct arrow
{
	int				angle;
	sf::Vector2f	coord;
	sf::Vector2f	dirVec;
	sf::Sprite		sprite;
};


class Tower
{
	private:

	sf::Texture		*weaponTextureArr;
	sf::Texture		*arrowTexture;

	sf::Sprite		towerSprite;
	sf::Sprite		weaponSprite;

	sf::Vector2f	towerCoord; // Tile coordinates, NOT pixels!!

	sf::Clock		towerClock;
	sf::Clock		shootingClock;

	std::vector<arrow>	arrowVec;

	int				weaponAngle;
	int				weaponIdleAngle;
	int				idleAngleIncrement;

	int				attackRadius;

	bool 			firstShotFired;
	bool			isShooting;
	int				weaponAnimIterator;


	public:

	Tower(sf::Texture &towerText, sf::Texture *weaponTextArr, sf::Texture *arrowText, sf::Vector2f towerCoord);
	~Tower() {};

	void	drawTower(sf::RenderWindow &window);
	bool	isVisible(int *xDrawLimits, int *yDrawLimits);
	bool	isSnakeVisible(sf::Vector2f snakeWorldCoord);

	void	shootArrow(sf::Vector2f snakePos);


	void	setAngle(int newAngle);
	void	setIdleAngle();
	void	setAttackAngle(sf::Vector2f snakePos);
	void	setShootingFlag(bool value);

	sf::Vector2f	getPosInPixels();
	sf::Sprite		&getSprite();
	sf::Sprite		&getWeaponSprite();
	int				&getWeaponAngle();

};


#endif