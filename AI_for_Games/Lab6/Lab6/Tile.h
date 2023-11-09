#ifndef TILE_H
#define TILE_H

#include "TileType.h"

class Tile {
public:
	Tile(int t_x, int t_y, TileType t_type);
	int getX() const;
	int getY() const;
	TileType getType() const;
	sf::RectangleShape& getRect();
	int& getDistance();
	void setType(TileType t_type);
	void render(sf::RenderWindow& t_window);

	int calculateTileDistance(int t_x, int t_y);
	void setDistance(int t_distance);
	sf::Color getColorBasedOnDistance();
	void setColor(sf::Color t_color);

	void setFlowVector(sf::Vector2f t_flowVector);
	sf::Vector2f getFlowVector() const;
	void drawFlowVector(sf::RenderWindow& window);

private:
	int m_x, m_y; // X & Y index
	TileType m_type;
	sf::RectangleShape m_rect;
	int m_distance;
	sf::Text m_distanceText;
	sf::Color m_color;
	sf::Vector2f m_flowVector;
};

#endif