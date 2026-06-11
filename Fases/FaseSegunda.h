#pragma once
#include "Fase.h"
#include "../Entidades/Personagens/Cobra.h"
#include "../Entidades/Personagens/Shogun.h"
#include "../Entidades/Obstaculos/Espinho.h"
#include <SFML/Graphics.hpp>

class FaseSegunda : public Fase {
public:
    FaseSegunda(Mapa1& mapa);
    ~FaseSegunda();
    bool faseFinalizada() const override;
    void verificarTransicaoFase(Ninja& jogador);

protected:
    void criarInimigos(Mapa1& mapa) override;
    void criarObstaculos(Mapa1& mapa) override;
    void criarFinal(Mapa1& mapa) override;

private:
    Shogun* shogunBoss = nullptr;
};
