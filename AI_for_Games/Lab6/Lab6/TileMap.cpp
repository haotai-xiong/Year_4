#include "TileMap.h"

TileMap::TileMap() {
	tiles.resize(height_Num, std::vector<Tile>(width_Num, Tile(0, 0, TileType::Traversable)));


	for (int y = 0; y < height_Num; y++) {
		for (int x = 0; x < width_Num; x++) {
			tiles[y][x] = Tile(x, y, TileType::Traversable);
		}
	}

	// start point setup
	tiles[5][15].setType(TileType::Start);
	tiles[5][15].setColor(tileTypeToColor[TileType::Start]);
	// destination setup
	tiles[m_destination.y][m_destination.x].setType(TileType::Destination);
	tiles[m_destination.y][m_destination.x].setColor(tileTypeToColor[TileType::Destination]);

	for (int y = 0; y < height_Num; y++) {
		for (int x = 0; x < width_Num; x++) {
			tiles[y][x].setDistance(tiles[y][x].calculateTileDistance(25, 40));

			if (TileType::Traversable == tiles[y][x].getType())
			{
				tiles[y][x].setColor(tiles[y][x].getColorBasedOnDistance());
			}
		}
	}

	createFlowField();

	// random generating numbers to set non-traversable tiles for testing purpose
	/*
	for (int i = 0; i < 20; i++) {
		int randX = rand() % width_Num;
		int randY = rand() % height_Num;

		tiles[randY][randX].setType(TileType::NonTraversable);
	}
	*/
}

Tile* TileMap::getTile(int t_x, int t_y) {
	if (t_x >= 0 && t_x < width_Num && t_y >= 0 && t_y < height_Num) {
		return &tiles[t_y][t_x];
	}
	return nullptr;
}

void TileMap::setTile(int t_x, int t_y, TileType t_type) {
	if (Tile* tile = getTile(t_x, t_y)) {
		tile->setType(t_type);
	}
}

void TileMap::render(sf::RenderWindow& t_window) {
	for (int y = 0; y < height_Num; y++) {
		for (int x = 0; x < width_Num; x++) {
			tiles[y][x].render(t_window);
		}
	}
}

void TileMap::generateIntegrationField() {

}

void TileMap::createFlowField() {
	for (int y = 0; y < height_Num; y++) {
		for (int x = 0; x < width_Num; x++) {
			sf::Vector2f flowVector(0.0f, 0.0f);
			int minDistance = std::numeric_limits<int>::max();

			for (const auto& dir : directions) {
				sf::Vector2i neighborPos = sf::Vector2i(x, y) + dir;

				if (isValid(neighborPos)) {
					int neighborDistance = tiles[neighborPos.y][neighborPos.x].calculateTileDistance(m_destination.x, m_destination.y);
					if (neighborDistance < minDistance) {
						minDistance = neighborDistance;
						flowVector = sf::Vector2f(dir);
					}
				}
			}

			if (minDistance < std::numeric_limits<int>::max()) {
				float length = std::sqrt(flowVector.x * flowVector.x + flowVector.y * flowVector.y);
				if (length > 0.0f) {
					flowVector /= length;
				}
			}

			// Store the flow vector in the tile
			tiles[y][x].setFlowVector(flowVector);
		}
	}
}

bool TileMap::isValid(const sf::Vector2i& t_pos)
{
	return t_pos.x >= 0 && t_pos.x < width_Num && t_pos.y >= 0 && t_pos.y < height_Num 
		&& TileType::Traversable == tiles[t_pos.y][t_pos.x].getType();
}
