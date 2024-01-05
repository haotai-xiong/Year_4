#include "TileMap.h"

TileMap::TileMap() {
	tiles.resize(height_Num, std::vector<Tile>(width_Num, Tile(sf::Vector2i(0, 0), TileType::None, TileColor::Transparent)));
	for (int y = 0; y < height_Num; y++) {
		for (int x = 0; x < width_Num; x++) {
			tiles[y][x] = Tile(sf::Vector2i(x, y), TileType::None, TileColor::Transparent);
		}
	}
}

Tile* TileMap::getTile(sf::Vector2i t_pos) {
	if (t_pos.x >= 0 && t_pos.x < width_Num && t_pos.y >= 0 && t_pos.y < height_Num) {
		return &tiles[t_pos.y][t_pos.x];
	}
	return nullptr;
}

void TileMap::setTile(sf::Vector2i t_pos, TileType t_type, TileColor t_color) {
	if (Tile* tile = getTile(t_pos)) {
		tile->setType(t_type);
		tile->setColor(t_color);
	}
}

void TileMap::update() {
}

void TileMap::render(sf::RenderWindow& t_window)
{
	for (int y = 0; y < height_Num; y++) {
		for (int x = 0; x < width_Num; x++) {
			tiles[y][x].render(t_window);
		}
	}
}

bool TileMap::canPlaceTile(sf::Vector2i t_index, TileType t_type, TileColor t_color) {
    if (getTile(t_index)->getType() != TileType::None) {
        return false;
    }

    std::vector<std::pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
    for (const auto& dir : directions) {
        int adjX = t_index.x + dir.first;
        int adjY = t_index.y + dir.second;

        // boundaries
        if (adjX < 0 || adjX >= width_Num || adjY < 0 || adjY >= height_Num) {
            continue;
        }

        const Tile& adjacentTile = tiles[adjY][adjX];
        if (adjacentTile.getType() != TileType::None) {
            // same shape, different color or same color, different shape
            if (!((t_type == adjacentTile.getType() && t_color != adjacentTile.getColor()) ||
                (t_color == adjacentTile.getColor() && t_type != adjacentTile.getType()))) {
                return false;
            }
        }
    }
    return true;
}