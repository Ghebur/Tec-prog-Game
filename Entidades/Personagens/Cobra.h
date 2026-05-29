#pragma once
#include "Inimigos.h"
#include "../../Fases/Mapas.h"
#include <cmath>

class Cobra : public Inimigo {
    private:
        sf::RectangleShape corpo;
        sf::Clock relogio;
        float origemX;
    public:
        Cobra(float x, float y);
        ~Cobra();
        void movimentaçao() override;
        void danifcar() override;
        void desenhar(sf::RenderWindow& window);
        void update(Mapa1& mapa, Personagens& p);
        sf::FloatRect getBounds() override { return {posicao, corpo.getSize()}; }
};