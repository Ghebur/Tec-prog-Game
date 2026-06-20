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
    FlechaShogun* criarProjeteis(sf::Vector2f pos, float dirX) override;

protected:
    void criarInimigos(Mapa1& mapa) override;
    void criarInimigosDificeis(Mapa1& mapa);
    void criarObstaculos(Mapa1& mapa) override;
    void criarFinal(Mapa1& mapa) override;
    //void carregarFase() override;

private:
    Shogun* shogunBoss = nullptr;
    Shogun* shogunA    = nullptr;
    Shogun* shogunB    = nullptr;
    Shogun* shogunRand = nullptr;
};
