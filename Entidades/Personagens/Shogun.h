#pragma once
#include "Inimigos.h"
#include "Personagens.h"
#include "../../Fases/Mapas.h"
#include <cmath>

class Shogun : public Inimigo {
    private:
        sf::RectangleShape corpo;
        float origemX;
        float angulo = 0.f;
        int graduacao;
        sf::Texture texRun;
        sf::Sprite sprite{texRun};
        sf::Clock relogioAnim;

        enum class EstadoAnim {RUNNING};
        static constexpr int FRAME_W = 128;
        static constexpr int FRAME_H = 128;
    public:
        Shogun(float x, float y);
        ~Shogun();
        void executar() override {}
        void movimentacao() override;
        void danifcar(Personagens& p) override;
        void atualizarAnimacao();
        void desenhar(sf::RenderWindow& window);
        void update(Mapa1& mapa, Personagens& p);
        sf::FloatRect getBounds() override { return {posicao, corpo.getSize()}; }
};
