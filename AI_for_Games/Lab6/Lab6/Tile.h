#ifndef TILE_HPP
#define TILE_HPP

enum class TileType {
	Traversable,
	NonTraversable
};

class Tile {
public:
	Tile(int t_x, int t_y, TileType t_type);
	int getX() const;
	int getY() const;
	TileType getType() const;
	void setType(TileType t_type);

private:
	int m_x, m_y;
	TileType m_type;
};

#endif