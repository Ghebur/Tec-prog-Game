#pragma once
#include <SFML/Graphics.hpp>

class Figura {
private:
    sf::Sprite sprite;
public:
    explicit Figura(sf::Texture& tex);
    void desenhar(sf::RenderWindow& window);
    sf::Sprite& getSprite();
};
