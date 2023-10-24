#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <vector>
#include "Tile.h"

class TileMap {
public:
	TileMap();
	Tile* getTile(int t_x, int t_y);
	void setTile(int t_x, int t_y, TileType t_type);

private:
	std::vector<std::vector<Tile>> tiles;
	int width_Num = screen
};

#endif