#include "UIPanel.h"

void UIPanel::update(const sf::RenderWindow& t_window) {
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(t_window));
    m_hovered = panelShape.getGlobalBounds().contains(mousePos);
    float targetX = hovered() ? screenSize.x - width : screenSize.x - width / 10.0f;
    float panelX = panelShape.getPosition().x;
    float m_speed = 10.0f;
    panelX += (targetX - panelX) / m_speed;
    panelShape.setPosition(sf::Vector2f(panelX, screenSize.y - height));

    for (const auto& config : buttonConfigs) {
        std::pair<TileType, TileColor> key = { config.m_type, config.m_color };
        auto& button = buttons[key];
        button.setPosition(panelShape.getPosition() + config.m_positionOffset);
    }
}

void UIPanel::render(sf::RenderWindow& t_window) {
    t_window.draw(panelShape);

    for (const auto& [key, button] : buttons) {
        t_window.draw(button);
    }
}

void UIPanel::processEvent(sf::Event& t_event, sf::RenderWindow& t_window, TileMap& t_map) {
    if (sf::Event::MouseButtonPressed == t_event.type) {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(t_window));
        if (hovered()) {
            handleMouseClick(mousePos);
        }
        else {
            auto selectedOption = getSelectedOption();
            if (selectedOption.first != TileType::None
                && selectedOption.second != TileColor::Transparent) {

                sf::Vector2f worldPos = t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window));
                // check if the chess is placable or not
                if (t_map.canPlaceTile(worldToTileCoordIndex(worldPos), selectedOption.first, selectedOption.second)) {
                    t_map.addChess(worldToTileCoordIndex(worldPos), selectedOption.first, selectedOption.second);
                    // Reset the selection after placing a building
                    resetSelection();
                    t_map.AIPlaceChess();
                }
            }
        }
    }
}

void UIPanel::handleMouseClick(const sf::Vector2f& mousePos) {
    for (const auto& [key, button] : buttons) {
        if (button.getGlobalBounds().contains(mousePos)) {
            selectedOption = key;
            break;
        }
    }
}

void UIPanel::buttonSetup() {
    for (const auto& config : buttonConfigs) {
        sf::Sprite button;
        button.setTexture(m_textureManager.getTexture(TileType_to_String[config.m_type]));
        button.setColor(ColorTypeToColor[config.m_color]);
        resizeToTileSize(button);

        std::pair<TileType, TileColor> key = { config.m_type, config.m_color };
        buttons[key] = button;
    }
}