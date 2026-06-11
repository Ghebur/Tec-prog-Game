#pragma once
#include "Inimigos.h"
#include "../../Fases/Mapas.h"
#include <cmath>

class Cobra : public Inimigo {
    private:
        sf::RectangleShape corpo;
        float origemX;
        float angulo = 0.f;
        bool venenosa;
        sf::Texture texRun;
        sf::Sprite sprite{texRun};
        sf::Clock relogioAnim;

        static constexpr int FRAME_W = 48;
        static constexpr int FRAME_H = 48;
    public:
        Cobra(float x, float y);
        ~Cobra();
        void executar() override {}
        void movimentacao() override;
        void danifcar(Personagens& p) override;
        void atualizarAnimacao();
        void desenhar(sf::RenderWindow& window);
        void update(Mapa1& mapa, Personagens& p);
        sf::FloatRect getBounds() override { return {posicao, corpo.getSize()}; }
};