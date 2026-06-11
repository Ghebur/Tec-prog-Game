#pragma once
#include "Inimigos.h"
#include "Personagens.h"
#include "../../Fases/Mapas.h"
#include "../FlechaShogun.h"
#include <cmath>

class Shogun : public Inimigo {
private:
    sf::RectangleShape corpo;
    float origemX;
    float angulo = 0.f;
    bool olhandoDireita = true;

    sf::Texture texIdle, texRun, texShot;
    sf::Sprite sprite{texIdle};
    sf::Clock relogioAnim;
    sf::Clock relogioTiro;

    enum class Estado { IDLE, RUNNING, SHOOTING };
    Estado estado = Estado::RUNNING;

    static constexpr int FRAME_W        = 128;
    static constexpr int FRAME_H        = 128;
    static constexpr int FRAMES_IDLE    = 9;
    static constexpr int FRAMES_RUN     = 8;
    static constexpr int FRAMES_SHOT    = 14;
    static constexpr float DIST_TIRO    = 300.f; // px
    static constexpr float INTERVALO_TIRO = 7.f; // segundos

    FlechaShogun* projetilPendente = nullptr;

    void atualizarAnimacao(Personagens& alvo);
    void entrarModoTiro();

public:
    Shogun(float x, float y);
    ~Shogun();
    void executar() override {}
    void movimentacao() override;
    void danifcar(Personagens& p) override;
    void desenhar(sf::RenderWindow& window) override;
    void update(Mapa1& mapa, Personagens& p) override;
    Projetil* getProjetilPendente() override;
    sf::FloatRect getBounds() override { return {posicao, corpo.getSize()}; }
};
