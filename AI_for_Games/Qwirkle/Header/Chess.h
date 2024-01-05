#ifndef BUILDINGS_H
#define BUILDINGS_H

#include "Globals.h"

class Chess {
public:
    Chess(const sf::Vector2i& t_pos, std::string t_textureName, TileColor t_color) : m_pos(t_pos) {}
    virtual ~Chess() {}

    sf::Vector2i pos() const { return m_pos; }
    void pos(sf::Vector2i& t_pos) { m_pos = std::move(t_pos); }

    virtual void render(sf::RenderWindow& t_window) const {
        t_window.draw(m_sprite);
    }

protected:
    sf::Vector2i m_pos;
    sf::Sprite m_sprite;
};

class Circle : public Chess {
public:
    Circle(const sf::Vector2i& t_pos, std::string t_textureName, TileColor t_color) : Chess(t_pos, t_textureName, t_color) {
        m_sprite.setTexture(m_textureManager.getTexture(t_textureName));
        resizeToTileSize(m_sprite);
        m_sprite.setColor(ColorTypeToColor[t_color]);
    }
};

#endif