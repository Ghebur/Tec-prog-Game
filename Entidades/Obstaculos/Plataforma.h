#pragma once
#include <SFML/Graphics.hpp>
#include "Obstaculos.h"

class Plataforma : public Obstaculos {
    private:
        sf::RectangleShape plataforma;
    public:
        Plataforma(float x, float y);
        ~Plataforma();
        void desenhar(sf::RenderWindow& window) override;
        void obstaculizar(Personagens& p) override;
};
