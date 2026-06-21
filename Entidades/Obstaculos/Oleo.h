#pragma once
#include <SFML/Graphics.hpp>
#include "Obstaculos.h"

namespace Obstaculos {

class oleo : public Obstaculos {
    private:
        sf::RectangleShape forma;
        sf::Texture tex;
        sf::Sprite sprite{tex};
        sf::Vector2f posBase;
        float larguraTile;
        sf::Clock relogioVisc;
        float viscosidade = 1.f;

    public:
        oleo(sf::Vector2f pos, sf::Vector2f tamanho = sf::Vector2f(50.f, 50.f));
        ~oleo();
        float variaViscosidade();
        void executar() override;
        void obstaculizar(Personagens::Personagens& p) override;
        void desenhar(sf::RenderWindow& window) override;
        void salvar() override;
};

} // namespace Obstaculos
