#ifndef UIPANEL_H
#define UIPANEL_H

#include "TileMap.h"

class UIPanel {
public:
    /*
    enum class BuildingOption {
        None,
        Circle,
        Diamond,
        Paper,
        Scissor,
        Square,
        Triangle
    }
    */

    std::pair<TileType, TileColor> selectedOption;

    struct ButtonData {
        // std::string m_textureName;
        sf::Vector2f m_positionOffset;
        TileType m_type;
        TileColor m_color;
    };

    UIPanel(float t_width = 200.0f, float t_height = 500.0f, sf::Vector2f t_screenSize = sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT))
        : width(t_width), height(t_height), screenSize(t_screenSize), m_hovered(false) {
        panelShape.setSize(sf::Vector2f(width, height));
        panelShape.setFillColor(sf::Color(100, 100, 100, 200)); // Semi-transparent
        panelShape.setPosition(sf::Vector2f(screenSize.x - t_width / 10.0f, screenSize.y - height));

        buttonSetup();
    }

    void update(const sf::RenderWindow& t_window);
    void render(sf::RenderWindow& t_window);
    void processEvent(sf::Event& t_event, sf::RenderWindow& t_window, TileMap& t_map);

    void handleMouseClick(const sf::Vector2f& mousePos);
    std::pair<TileType, TileColor> getSelectedOption() const { return selectedOption; }
    void resetSelection() { selectedOption = std::make_pair(TileType::None, TileColor::Transparent); }
    bool hovered() const { return m_hovered; }

private:
    
    void buttonSetup();

    float width;
    float height;
    float UI_SHRINK_WIDTH = 5.0f;
    sf::Vector2f screenSize;
    sf::RectangleShape panelShape;
    bool m_hovered;

    std::map<std::pair<TileType, TileColor>, sf::Sprite> buttons;

    std::vector<ButtonData> buttonConfigs = {
        // circle
        {sf::Vector2f(10.0f, 0.0f), TileType::Circle, TileColor:: Red},
        {sf::Vector2f(10.0f, 40.0f), TileType::Circle, TileColor:: Blue},
        {sf::Vector2f(10.0f, 80.0f), TileType::Circle, TileColor:: Green},
        {sf::Vector2f(10.0f, 120.0f), TileType::Circle, TileColor:: Yellow},
        {sf::Vector2f(10.0f, 160.0f), TileType::Circle, TileColor:: Purple},
        {sf::Vector2f(10.0f, 200.0f), TileType::Circle, TileColor:: Orange},
        // square
        {sf::Vector2f(10.0f, 240.0f), TileType::Square, TileColor::Red},
        {sf::Vector2f(10.0f, 280.0f), TileType::Square, TileColor::Blue},
        {sf::Vector2f(10.0f, 320.0f), TileType::Square, TileColor::Green},
        {sf::Vector2f(10.0f, 360.0f), TileType::Square, TileColor::Yellow},
        {sf::Vector2f(10.0f, 400.0f), TileType::Square, TileColor::Purple},
        {sf::Vector2f(10.0f, 440.0f), TileType::Square, TileColor::Orange},
        // diamond
        {sf::Vector2f(70.0f, 0.0f), TileType::Diamond, TileColor::Red},
        {sf::Vector2f(70.0f, 40.0f), TileType::Diamond, TileColor::Blue},
        {sf::Vector2f(70.0f, 80.0f), TileType::Diamond, TileColor::Green},
        {sf::Vector2f(70.0f, 120.0f), TileType::Diamond, TileColor::Yellow},
        {sf::Vector2f(70.0f, 160.0f), TileType::Diamond, TileColor::Purple},
        {sf::Vector2f(70.0f, 200.0f), TileType::Diamond, TileColor::Orange},
        // triangle   
        {sf::Vector2f(70.0f, 240.0f), TileType::Triangle, TileColor::Red},
        {sf::Vector2f(70.0f, 280.0f), TileType::Triangle, TileColor::Blue},
        {sf::Vector2f(70.0f, 320.0f), TileType::Triangle, TileColor::Green},
        {sf::Vector2f(70.0f, 360.0f), TileType::Triangle, TileColor::Yellow},
        {sf::Vector2f(70.0f, 400.0f), TileType::Triangle, TileColor::Purple},
        {sf::Vector2f(70.0f, 440.0f), TileType::Triangle, TileColor::Orange},
        // paper
        {sf::Vector2f(130.0f, 0.0f), TileType::Paper, TileColor::Red},
        {sf::Vector2f(130.0f, 40.0f), TileType::Paper, TileColor::Blue},
        {sf::Vector2f(130.0f, 80.0f), TileType::Paper, TileColor::Green},
        {sf::Vector2f(130.0f, 120.0f), TileType::Paper, TileColor::Yellow},
        {sf::Vector2f(130.0f, 160.0f), TileType::Paper, TileColor::Purple},
        {sf::Vector2f(130.0f, 200.0f), TileType::Paper, TileColor::Orange},
        // scissor     
        {sf::Vector2f(130.0f, 240.0f), TileType::Scissor, TileColor::Red},
        {sf::Vector2f(130.0f, 280.0f), TileType::Scissor, TileColor::Blue},
        {sf::Vector2f(130.0f, 320.0f), TileType::Scissor, TileColor::Green},
        {sf::Vector2f(130.0f, 360.0f), TileType::Scissor, TileColor::Yellow},
        {sf::Vector2f(130.0f, 400.0f), TileType::Scissor, TileColor::Purple},
        {sf::Vector2f(130.0f, 440.0f), TileType::Scissor, TileColor::Orange},
    };
};

#endif // !UIPANEL_H