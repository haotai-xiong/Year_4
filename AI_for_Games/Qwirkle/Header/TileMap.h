#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include "Tile.h"
#include "Chess.h"

class TileMap {
public:
	TileMap();
	void render(sf::RenderWindow& t_window);
    void update();

    Tile* getTile(sf::Vector2i t_pos);
    void setTile(sf::Vector2i t_pos, TileType t_type, TileColor t_color);
    int getWidthNum() const { return width_Num; }
    int getHeightNum() const { return height_Num; }

    void addChess(sf::Vector2i t_pos, TileType tileType, TileColor tileColor) {
        // m_chess.push_back(std::make_unique<Chess>(t_pos, textureName, tileColor));
        setTile(t_pos, tileType, tileColor);
    }

    void renderChess(sf::RenderWindow& window) {
        for (const auto& chess : m_chess) {
            chess->render(window);
        }
    }

    bool canPlaceTile(sf::Vector2i t_index, TileType t_type, TileColor t_color);

    void AIPlaceChess() {
        bool shouldBreakOuterLoop = false;
        for (int y = 0; y < height_Num && !shouldBreakOuterLoop; y++) {
            for (int x = 0; x < width_Num; x++) {
                if (tiles[y][x].getType() != TileType::None) {
                    // get available color and shapes
                    std::vector<TileType> availableTypes {TileType::Circle, TileType::Diamond, TileType::Square,
                                                        TileType::Triangle, TileType::Paper, TileType::Scissor};
                    availableTypes.erase(std::remove(availableTypes.begin(), availableTypes.end(), tiles[y][x].getType()), 
                        availableTypes.end());
                    TileColor availableColor = tiles[y][x].getColor();

                    // check for available position
                    std::vector<sf::Vector2i> availablePositions;
                    std::vector<std::pair<int, int>> directions = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

                    for (const auto& dir : directions) {
                        sf::Vector2i newPos = sf::Vector2i(x, y) + sf::Vector2i(dir.first, dir.second);

                        // Check boundaries and if the new position is free
                        if (newPos.x >= 0 && newPos.x < width_Num && newPos.y >= 0 && newPos.y < height_Num
                            && getTile(newPos)->getType() == TileType::None) {
                            availablePositions.push_back(newPos);
                        }
                    }

                    if (!availablePositions.empty())
                    {
                        int randomDirection = std::rand() % availablePositions.size();
                        int randomShape = std::rand() % availableTypes.size();
                        addChess(availablePositions.at(randomDirection), availableTypes.at(randomShape), availableColor);
                        shouldBreakOuterLoop = true;
                        break;
                    }
                }
            }
        }
    }

private:

	std::vector<std::vector<Tile>> tiles;
	int width_Num = SCREEN_WIDTH / TILE_SIZE;
	int height_Num = SCREEN_HEIGHT / TILE_SIZE;

    std::vector<std::unique_ptr<Chess>> m_chess;
};

#endif