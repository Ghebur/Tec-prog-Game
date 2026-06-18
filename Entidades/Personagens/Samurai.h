#pragma once
#include "Inimigos.h"
#include "Personagens.h"
#include "../../Fases/Mapas.h"
#include <cmath>

class Samurai : public Inimigo {
    private:
        sf::RectangleShape corpo;
        int graduacao;
        sf::Texture texRun;
        sf::Sprite sprite{texRun};
        sf::Clock relogioAnim;
        float ultimoSin = 0.f;

        static constexpr int FRAME_W = 128;
        static constexpr int FRAME_H = 128;
    public:
        Samurai(float x, float y);
        ~Samurai();
        void executar() override {}
        void danifcar(Personagens& p) override;
        void atualizarAnimacao() override;
        void pular();
        void desenhar(sf::RenderWindow& window);
        void executar(Mapa1& mapa, Personagens& p);
        sf::FloatRect getBounds() override { return {posicao, corpo.getSize()}; }
        void salvar() override;
};