#pragma once
#include "Inimigos.h"
#include "Personagens.h"
#include "../../Fases/Mapas.h"
#include "../FlechaShogun.h"
#include <cmath>

namespace Fases { class Fase; }

namespace Personagens {

class Shogun : public Inimigo {
private:
    sf::RectangleShape corpo;
    bool olhandoDireita = true;

    sf::Texture texIdle, texRun, texShot;
    sf::Clock relogioAnim;
    sf::Clock relogioTiro;

    enum class Estado { IDLE, RUNNING, SHOOTING };
    Estado estado = Estado::RUNNING;

    static constexpr int FRAME_W        = 128;
    static constexpr int FRAME_H        = 128;
    static constexpr int FRAMES_IDLE    = 9;
    static constexpr int FRAMES_RUN     = 8;
    static constexpr int FRAMES_SHOT    = 14;
    static constexpr float DIST_TIRO    = 300.f;
    static constexpr float INTERVALO_TIRO = 7.f;

    Fases::Fase* fase;

    void atualizarAnimacao(Personagens& alvo);
    void entrarModoTiro();

public:
    Shogun(float x, float y, Fases::Fase* fase);
    ~Shogun();
    void executar() override {}
    bool movimentacao() override;
    void danifcar(Personagens& p) override;
    void executar(Mapa1& mapa, Personagens& p) override;
    sf::FloatRect getBounds() override { return {posicao, corpo.getSize()}; }
    void salvar() override;
};

} // namespace Personagens
