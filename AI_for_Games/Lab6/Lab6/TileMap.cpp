#include "TileMap.h"

TileMap::TileMap() {
	tiles.resize(height_Num, std::vector<Tile>(width_Num, Tile(sf::Vector2i(0, 0), TileType::Traversable)));

	for (int y = 0; y < height_Num; y++) {
		for (int x = 0; x < width_Num; x++) {
			tiles[y][x] = Tile(sf::Vector2i(x, y), TileType::Traversable);
			tiles[y][x].cost(1);
		}
	}

	specialTileSetup();
	generateIntegrationField();
	createFlowField();
	drawPath(m_startPoint);
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
	for (int y = 0; y < height_Num; y++) {
		for (int x = 0; x < width_Num; x++) {
			tiles[y][x].setDistance(tiles[y][x].calculateTileDistance(m_destination.x, m_destination.y));

			if (TileType::Traversable == tiles[y][x].getType())
			{
				tiles[y][x].setColor(tiles[y][x].getColorBasedOnDistance());
			}
		}
	}
}

void TileMap::createFlowField() {
	for (int y = 0; y < height_Num; y++) {
		for (int x = 0; x < width_Num; x++) {
			sf::Vector2f flowVector(0.0f, 0.0f);
			int minCostDistance = std::numeric_limits<int>::max();

			for (const auto& dir : directions) {
				sf::Vector2i neighborPos = sf::Vector2i(x, y) + dir;

				if (isValid(neighborPos)) {
					int neighborDistance = tiles[neighborPos.y][neighborPos.x].calculateTileDistance(m_destination.x, m_destination.y);
					int pathCost = tiles[neighborPos.y][neighborPos.x].cost();
					int costDistance = neighborDistance + pathCost;

					if (costDistance < minCostDistance) {
						minCostDistance = costDistance;
						flowVector = sf::Vector2f(dir);
					}
				}
			}
			tiles[y][x].setFlowVector(flowVector);
		}
	}
}

void TileMap::drawPath(sf::Vector2i t_pos) {
	if (t_pos.x < 0 || t_pos.x >= width_Num || t_pos.y < 0 || t_pos.y >= height_Num
		|| TileType::Destination == tiles[t_pos.y][t_pos.x].getType()) {
		return;
	}

	/*
	if (TileType::Destination != tiles[t_pos.y][t_pos.x].getType()) {
		tiles[t_pos.y][t_pos.x].getRect().setFillColor(sf::Color::Yellow);
		sf::Vector2i tempFlowVec = static_cast<sf::Vector2i>(tiles[t_pos.y][t_pos.x].getFlowVector());
		sf::Vector2i nextPos = t_pos + tempFlowVec;
		drawPath(nextPos);
	}
	*/

	sf::Vector2i nextPos;

	sf::Vector2i tempFlowVec = static_cast<sf::Vector2i>(tiles[t_pos.y][t_pos.x].getFlowVector());
	nextPos = t_pos + tempFlowVec;

	for (int i = 0; i < 100; i++)
	{
		if (isNeighbourDestination(t_pos))
		{
			break;
		}

		if (TileType::Destination != tiles[nextPos.y][nextPos.x].getType()) {
			tiles[nextPos.y][nextPos.x].getRect().setFillColor(sf::Color::Yellow);
			sf::Vector2i tempFlowVec = static_cast<sf::Vector2i>(tiles[nextPos.y][nextPos.x].getFlowVector());
			nextPos += tempFlowVec;
		}
	}
}

void TileMap::specialTileSetup() {
	// start point setup
	tiles[m_startPoint.y][m_startPoint.x].setType(TileType::Start);
	tiles[m_startPoint.y][m_startPoint.x].setColor(tileTypeToColor[TileType::Start]);
	// destination setup
	tiles[m_destination.y][m_destination.x].setType(TileType::Destination);
	tiles[m_destination.y][m_destination.x].setColor(tileTypeToColor[TileType::Destination]);
	tiles[m_destination.y][m_destination.x].cost(0);

	// random generating numbers to set non-traversable tiles for testing purpose
	for (int i = 0; i < 200; i++) {
		int randX = rand() % width_Num;
		int randY = rand() % height_Num;

		if (TileType::Destination != tiles[randY][randX].getType()) {
			tiles[randY][randX].setType(TileType::NonTraversable);
			tiles[randY][randX].getRect().setFillColor(tileTypeToColor[TileType::NonTraversable]);
			tiles[m_destination.y][m_destination.x].cost(999);
		}
	}
}

bool TileMap::isValid(const sf::Vector2i& t_pos) {
	return t_pos.x >= 0 && t_pos.x < width_Num && t_pos.y >= 0 && t_pos.y < height_Num
		&& TileType::Traversable == tiles[t_pos.y][t_pos.x].getType();
}

bool TileMap::isNeighbourDestination(sf::Vector2i t_pos) {
	for (const auto& dir : directions) {
		sf::Vector2i neighbourPos = t_pos + dir;
		if (TileType::Destination == tiles[neighbourPos.y][neighbourPos.x].getType()) {
			return true;
		}
	}
	return false;
}