#pragma once
#include <SFML/Graphics.hpp>
#include "Obstaculos.h"

class BlocoFinal : public Obstaculos {
    private:
        sf::RectangleShape forma;
        bool atingido = false;

    public:
        BlocoFinal(sf::Vector2f pos);
        ~BlocoFinal();
        void obstaculizar(Personagens& p) override;
        void desenhar(sf::RenderWindow& window) override;
        bool foiAtingido() const;
};
