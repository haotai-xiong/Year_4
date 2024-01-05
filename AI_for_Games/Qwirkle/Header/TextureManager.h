#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

class TextureManager {
public:
    TextureManager() {
        // buildings
        loadTexture("none", "../Assets/Shape/None.png");
        loadTexture("circle", "../Assets/Shape/Circle.png");
        loadTexture("diamond", "../Assets/Shape/Diamond.png");
        loadTexture("paper", "../Assets/Shape/Paper.png");
        loadTexture("scissor", "../Assets/Shape/Scissor.png");
        loadTexture("square", "../Assets/Shape/Square.png");
        loadTexture("triangle", "../Assets/Shape/Triangle.png");
        // fonts
        loadFont("cheril", "../Assets/Font/CHERL.TTF");
        loadFont("cherii", "../Assets/Font/CHERI.TTF");
    }
    ~TextureManager() {}

    void loadTexture(const std::string t_name, const std::string t_filename) {
        sf::Texture texture;
        texture.loadFromFile(t_filename);
        textures[t_name] = texture;
    }

    void loadFont(const std::string t_name, const std::string t_filename) {
        sf::Font font;
        font.loadFromFile(t_filename);
        fonts[t_name] = font;
    }

    sf::Texture& getTexture(const std::string t_name) {
        return textures.at(t_name);
    }

    sf::Font& getFont(const std::string t_name) {
        return fonts.at(t_name);
    }

private:
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::Font> fonts;
};

#endif // TEXTURE_MANAGER_H