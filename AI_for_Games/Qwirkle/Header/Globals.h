#ifndef GLOBALS_H
#define GLOBALS_H

#include "TextureManager.h"

inline int SCREEN_WIDTH = 600;
inline int SCREEN_HEIGHT = 600;
inline int TILE_SIZE = 40;

inline sf::Color TransparentColor = sf::Color::Transparent;
inline sf::Color BlueColor = sf::Color::Blue;
inline sf::Color RedColor = sf::Color::Red;
inline sf::Color GreenColor = sf::Color::Green;
inline sf::Color YellowColor = sf::Color::Yellow;
inline sf::Color PurpleColor = sf::Color(128, 0, 128);
inline sf::Color OrangeColor = sf::Color(255, 165, 0);

inline TextureManager m_textureManager;

inline sf::Vector2f worldToTileCoordPos(const sf::Vector2f& t_point) {
    int tileX = static_cast<int>(t_point.x) / TILE_SIZE;
    int tileY = static_cast<int>(t_point.y) / TILE_SIZE;

    return sf::Vector2f(tileX * TILE_SIZE, tileY * TILE_SIZE);
}

inline sf::Vector2i worldToTileCoordIndex(const sf::Vector2f& t_point) {
    int tileX = static_cast<int>(t_point.x) / TILE_SIZE;
    int tileY = static_cast<int>(t_point.y) / TILE_SIZE;

    return sf::Vector2i(tileX, tileY);
}

inline void resizeToTileSize(sf::Sprite& t_sprite) {
    float scaleX = static_cast<float>(TILE_SIZE) / t_sprite.getLocalBounds().width;
    float scaleY = static_cast<float>(TILE_SIZE) / t_sprite.getLocalBounds().height;
    t_sprite.setScale(scaleX, scaleY);
}

inline const std::vector<sf::Vector2i> directions = {
        sf::Vector2i(0, -1),  // up
        sf::Vector2i(0, 1),   // down
        sf::Vector2i(-1, 0),  // left
        sf::Vector2i(1, 0)    // right
};

inline float distance(const sf::Vector2f& t_left, const sf::Vector2f& t_right) {
    sf::Vector2f delta = t_left - t_right;
    return std::sqrt(delta.x * delta.x + delta.y * delta.y);
}

inline int woodAmount = 0;
inline int metalAmount = 0;
inline int energyAmount = 0;
inline int wasteAmount = 0;
inline int prosperity = 0;

#endif // !GLOBALS_HPP