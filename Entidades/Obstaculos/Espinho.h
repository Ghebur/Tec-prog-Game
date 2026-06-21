#pragma once
#include <SFML/Graphics.hpp>
#include "Obstaculos.h"

namespace Obstaculos {

class Espinho : public Obstaculos {
    private:
        short int danosidade;
        sf::RectangleShape forma;
        sf::Texture tex;
        int contadorToques = 0;
        bool semDano = false;

        void contarToque();

    public:
        Espinho(sf::Vector2f pos, sf::Vector2f tam);
        ~Espinho();
        void executar() override;
        void obstaculizar(Personagens::Personagens& p) override;
        void salvar() override;
};

} // namespace Obstaculos
