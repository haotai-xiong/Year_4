#include "Tile.h"

Tile::Tile(sf::Vector2i t_pos, TileType t_type, TileColor t_colorType) : m_pos(t_pos), m_type(t_type), m_tileColor(t_colorType)
{
	m_sprite.setTexture(m_textureManager.getTexture(TileType_to_String[t_type]));
	m_sprite.setPosition(t_pos.x * TILE_SIZE, t_pos.y * TILE_SIZE);
	m_sprite.setColor(ColorTypeToColor[this->m_tileColor]);
	resizeToTileSize(m_sprite);
}

sf::Vector2i Tile::getPos() {
	return m_pos;
}

void Tile::setType(TileType t_type) {
	m_type = t_type;
	m_sprite.setTexture(m_textureManager.getTexture(TileType_to_String[t_type]));
}

TileType Tile::getType() const {
	return m_type;
}

void Tile::setColor(TileColor t_color) {
	m_tileColor = t_color;
	m_sprite.setColor(ColorTypeToColor[this->m_tileColor]);
}

TileColor Tile::getColor() const {
	return m_tileColor;
}

void Tile::render(sf::RenderWindow& t_window) {
	t_window.draw(m_sprite);
}