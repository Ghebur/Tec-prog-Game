#pragma once
#include "Inimigos.h"
#include "../../Fases/Mapas.h"
#include <cmath>

class Samurai : public Inimigo {
    private:
        sf::RectangleShape corpo;
        sf::Clock relogio;
        float origemX;
    public:
        Samurai(float x, float y);
        ~Samurai();
        void movimentaçao() override;
        void danifcar() override;
        void desenhar(sf::RenderWindow& window);
        void update(Mapa1& mapa, Personagens& p);
        void colidirComPersonagem(Personagens& p);
        sf::FloatRect getBounds() override { return {posicao, corpo.getSize()}; }
};