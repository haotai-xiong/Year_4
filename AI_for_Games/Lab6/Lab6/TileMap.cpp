#include "TileMap.h"

TileMap::TileMap() {
	tiles.resize(height, std::vector<Tile>(width, Tile(0, 0, TileType::Traversable)));
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			tiles[y][x] = Tile(x, y, TileType::Traversable);
		}
	}
}

Tile* TileMap::getTile(int t_x, int t_y) {
	if (t_x >= 0 && t_x < width && t_y >= 0 && t_y < height) {
		return &tiles[t_y][t_x];
	}
	return nullptr;
}

void TileMap::setTile(int t_x, int t_y, TileType t_type) {
	if (Tile* tile = getTile(t_x, t_y)) {
		tile->setType(t_type);
	}
}
