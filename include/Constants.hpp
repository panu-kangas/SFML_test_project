#ifndef CONSTANTS_HPP
# define CONSTANTS_HPP

# define PI				3.1415926

# define WINDOW_WIDTH	1056 // 33 tiles
# define WINDOW_HEIGHT	736 // 23 tiles
# define TILE_SIZE		32

# define VALID_MAP_CHAR	"01SCT"

# define SNAKE_INIT_SPEED	150
# define SNAKE_BOOST_SPEED	220

# define BOOST_MAX			100
# define BOOST_REDUCE		70
# define BOOST_REPLENISH	15

# define RED "\033[31m"
# define GREEN "\033[32m"
# define RESET "\033[0m"

enum	states
{
	StartScreen,
	LevelScreen,
	SnakeStill,
	SnakeMove,
	GameOver,
	Win,
};

#endif