#pragma once
#include <SFML/Graphics.hpp>
#include "Obstaculos.h"

class oleo : public Obstaculos {
    private:
        sf::RectangleShape forma;
    public:
        oleo(sf::Vector2f pos, sf::Vector2f tamanho = sf::Vector2f(80.f, 20.f));
        ~oleo();
        void obstaculizar(Personagens& p) override;
        void desenhar(sf::RenderWindow& window) override;
};