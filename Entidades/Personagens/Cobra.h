#pragma once
#include "Inimigos.h"
#include "../../Fases/Mapas.h"
#include <cmath>

namespace Personagens {

class Cobra : public Inimigo {
    private:
        sf::RectangleShape corpo;
        bool venenosa;
        sf::Texture texRun;
        sf::Clock relogioAnim;

        static constexpr int FRAME_W = 48;
        static constexpr int FRAME_H = 48;
    public:
        Cobra(float x, float y);
        ~Cobra();
        void executar() override {}
        void danifcar(Personagens& p) override;
        void atualizarAnimacao() override;
        void executar(Mapa1& mapa, Personagens& p);
        sf::FloatRect getBounds() override;
        void salvar() override;
        void setVenenosa(int v);
        void setAngulo(float a);
};

} // namespace Personagens