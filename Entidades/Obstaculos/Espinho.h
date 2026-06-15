#pragma once
#include <SFML/Graphics.hpp>
#include "Obstaculos.h"

class Espinho : public Obstaculos {
    private:
        short int danosidade;
        sf::RectangleShape forma;
        sf::Texture tex;
        sf::Sprite sprite{tex};

    public:
        Espinho(sf::Vector2f pos, sf::Vector2f tam);
        ~Espinho();
        void obstaculizar(Personagens& p) override;
        void desenhar(sf::RenderWindow& window) override;
        void salvar() override;
};
