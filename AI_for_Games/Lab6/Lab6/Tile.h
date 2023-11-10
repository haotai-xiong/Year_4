#ifndef TILE_H
#define TILE_H

#include "TileType.h"

class Tile {
public:
	Tile(sf::Vector2i t_pos, TileType t_type);
	// int getX() const;
	// int getY() const;
	sf::Vector2i& pos() { return m_pos; }
	void pos(sf::Vector2i t_pos) { m_pos = std::move(t_pos); }

	TileType getType() const;
	sf::RectangleShape& getRect();
	void setType(TileType t_type);
	void render(sf::RenderWindow& t_window);

	int calculateTileDistance(int t_x, int t_y);
	void setDistance(int t_distance);
	sf::Color getColorBasedOnDistance();
	void setColor(sf::Color t_color);

	void setFlowVector(sf::Vector2f t_flowVector);
	sf::Vector2f getFlowVector() const;
	void drawFlowVector(sf::RenderWindow& window);


	int& getDistance();
	int cost() const { return m_cost; }
	void cost(int t_cost) { m_cost = std::move(t_cost); }

private:
	// int m_x, m_y; // X & Y index
	sf::Vector2i m_pos;

	TileType m_type;
	sf::RectangleShape m_rect;
	int m_cost;
	int m_distance;
	sf::Text m_distanceText;
	sf::Color m_originColor;
	sf::Vector2f m_flowVector;
};

#endif