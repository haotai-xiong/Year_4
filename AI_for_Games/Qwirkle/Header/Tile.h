#ifndef TILE_H
#define TILE_H

#include "TileType.h"

class Tile {
public:
	Tile(sf::Vector2i t_pos, TileType t_type, TileColor t_colorType);
	sf::Vector2i getPos();
	void setType(TileType t_type);
	TileType getType() const;
	void setColor(TileColor t_color);
	TileColor getColor() const;
	void render(sf::RenderWindow& t_window);

private:
	sf::Vector2i m_pos; // X & Y index
	TileType m_type;
	TileColor m_tileColor;
	// sf::RectangleShape m_rect;
	sf::Sprite m_sprite;
};

#endif