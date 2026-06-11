#pragma once
#include <SFML/Graphics.hpp>
#include "Obstaculos.h"

class oleo : public Obstaculos {
    private:
        sf::RectangleShape forma;
        sf::Texture tex;
        sf::Sprite sprite{tex};
        sf::Vector2f posBase;
        float larguraTile;

    public:
        oleo(sf::Vector2f pos, sf::Vector2f tamanho = sf::Vector2f(50.f, 50.f));
        ~oleo();
        void obstaculizar(Personagens& p) override;
        void desenhar(sf::RenderWindow& window) override;
};
