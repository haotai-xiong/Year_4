#ifndef GLOBALS_H
#define GLOBALS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <queue>
#include <limits>
#include <stack>

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int TILE_WIDTH;
extern int TILE_HEIGHT;
extern sf::Color TraversableColor;
extern sf::Color NonTraversableColor;
inline sf::Color StartPointColor = sf::Color::White;
inline sf::Color DestinationColor = sf::Color::Red;
inline sf::Font Ariblk;
inline const std::vector<sf::Vector2i> directions = {
    {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1} // Including diagonals
};

#endif // !GLOBALS_HPP

