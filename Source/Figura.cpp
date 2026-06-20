#include "../Figura.h"

Figura::Figura(sf::Texture& tex) : sprite(tex) {}

void Figura::desenhar(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Sprite& Figura::getSprite() {
    return sprite;
}
