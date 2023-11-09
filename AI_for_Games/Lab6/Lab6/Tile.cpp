#include "Tile.h"

Tile::Tile(int t_x, int t_y, TileType t_type) : m_x(t_x), m_y(t_y), m_type(t_type), m_color(tileTypeToColor[this->m_type]) {
	m_distance = 0;

	Ariblk.loadFromFile("ASSETS/FONTS/ariblk.ttf");
	m_distanceText.setFont(Ariblk);
	m_distanceText.setCharacterSize(9.0f);
	m_distanceText.setFillColor(sf::Color::Black);

	m_rect.setSize(sf::Vector2f(TILE_WIDTH, TILE_HEIGHT));
	m_rect.setOutlineColor(sf::Color::Black);
	m_rect.setOutlineThickness(1.5f);

	m_rect.setPosition(t_x * TILE_WIDTH, t_y * TILE_HEIGHT);
	m_distanceText.setPosition((t_x + 0.15f) * TILE_WIDTH, (t_y + 0.15f) * TILE_HEIGHT);

	m_rect.setFillColor(m_color);
}

int Tile::getX() const {
	return m_x;
}

int Tile::getY() const {
	return m_y;
}

TileType Tile::getType() const {
	return m_type;
}

void Tile::setType(TileType t_type) {
	this->m_type = t_type;
}

void Tile::render(sf::RenderWindow& t_window) {
	m_distanceText.setString(std::to_string(m_distance));

	t_window.draw(m_rect);
	t_window.draw(m_distanceText);
	drawFlowVector(t_window);
}

// calculating how many tiles away from any t_tile
int Tile::calculateTileDistance(int t_x, int t_y) {
	return std::max(std::abs(t_x - m_x), std::abs(t_y - m_y));
}

void Tile::setDistance(int t_distance) {
	m_distance = t_distance;
}

sf::RectangleShape& Tile::getRect() {
	return m_rect;
}

int& Tile::getDistance() {
	return m_distance;
}

sf::Color Tile::getColorBasedOnDistance() {
	sf::Color currentColor = m_rect.getFillColor();
	int newRedIntensity = std::min(currentColor.r + m_distance * 4, 255);
	sf::Color newColor(newRedIntensity, currentColor.g, currentColor.b);

	return newColor;
}

void Tile::setColor(sf::Color t_color) {
	m_rect.setFillColor(t_color);
}

void Tile::setFlowVector(sf::Vector2f t_flowVector) {
	m_flowVector = t_flowVector;
}

sf::Vector2f Tile::getFlowVector() const {
	return m_flowVector;
}

void Tile::drawFlowVector(sf::RenderWindow& window) {
	if (TileType::Traversable == m_type || TileType::Start == m_type || TileType::Destination == m_type) {
		sf::VertexArray arrow(sf::Lines, 2);
		arrow[0].position = m_rect.getPosition() + sf::Vector2f(TILE_WIDTH / 2, TILE_HEIGHT / 2);
		arrow[1].position = arrow[0].position + (m_flowVector * 20.f);

		arrow[0].color = sf::Color::Magenta;
		arrow[1].color = sf::Color::Magenta;

		window.draw(arrow);
	}
}