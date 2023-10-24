#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "Globals.h"

enum class TileType {
	Traversable,
	NonTraversable
};

std::unordered_map<TileType, sf::Color> tileTypeToColor = {
	{TileType::Traversable, sf::Color::White},
	{TileType::NonTraversable, sf::Color::Black}
};

class Tile {
public:
	Tile(int t_x, int t_y, TileType t_type);
	int getX() const;
	int getY() const;
	TileType getType() const;
	void setType(TileType t_type);

private:
	int m_x, m_y;
	TileType m_type;
	sf::RectangleShape m_rect;
};

#endif