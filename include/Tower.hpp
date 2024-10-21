#ifndef TOWER_HPP
# define TOWER_HPP

# include <iostream>
# include <vector>
# include <SFML/Graphics.hpp>

# include "Constants.hpp"
# include "Arrow.hpp"



class Tower
{
	private:

	sf::Texture		*weaponTextureArr;
	sf::Texture		*arrowTexture;

	sf::Sprite		towerSprite;
	sf::Sprite		weaponSprite;

	sf::Vector2f	towerCoord; // Tile coordinates, NOT pixels!!

	const float		IdleAngleVelocity;
	sf::Clock		shootingClock;

	float			weaponAngle;
	float			weaponIdleAngle;

	int				attackRadius;

	bool 			firstShotFired;
	bool			isShooting;
	int				weaponAnimIterator;


	public:

	Tower(sf::Texture &towerText, sf::Texture *weaponTextArr, sf::Texture *arrowText, sf::Vector2f towerCoord);
	~Tower() {};

	void	drawTower(sf::RenderWindow &window, int &drawX, int &drawY, sf::Vector2f snakePos, float dt);

	bool	isVisible(int *xDrawLimits, int *yDrawLimits);
	bool	isSnakeVisible(sf::Vector2f snakeWorldCoord);

	void	shootArrow(sf::Vector2f snakePos, std::vector<Arrow> &arrowVec, bool snakeMoveStat);


	void	setAngle(int newAngle);
	void	setIdleAngle(float dt);
	void	setAttackAngle(sf::Vector2f snakePos);
	void	setShootingFlag(bool value);

	sf::Vector2f	getPosInPixels();
	sf::Vector2f	getMiddlePosInPixels();
	sf::Sprite		&getSprite();
	sf::Sprite		&getWeaponSprite();
	float			&getWeaponAngle();

};


#endif