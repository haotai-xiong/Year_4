#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include "Tile.h"

class TileMap {
public:
	TileMap();
	Tile* getTile(int t_x, int t_y);
	void setTile(int t_x, int t_y, TileType t_type);
	void render(sf::RenderWindow& t_window);
	
	void generateIntegrationField();
	void createFlowField();
	bool isValid(const sf::Vector2i& t_pos);

private:
	std::vector<std::vector<Tile>> tiles;
	int width_Num = SCREEN_WIDTH / TILE_WIDTH;
	int height_Num = SCREEN_HEIGHT / TILE_HEIGHT;

	sf::Vector2i m_destination = sf::Vector2i(25, 40);
	sf::Vector2i m_destination = sf::Vector2i(25, 40);
};

#endif