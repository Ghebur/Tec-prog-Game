#pragma once
#include <SFML/Graphics.hpp>
#include "Obstaculos.h"

namespace Obstaculos {

class Plataforma : public Obstaculos {
    private:
        sf::RectangleShape plataforma;
        sf::Texture textura;
        sf::Sprite sprite{textura};
    public:
        Plataforma(float x, float y);
        Plataforma(const Plataforma& other);
        ~Plataforma();
        void desenhar(sf::RenderWindow& window) override;
        void obstaculizar(Personagens::Personagens& p) override;
        void salvar() override;
        //void executar() override;
};

} // namespace Obstaculos
