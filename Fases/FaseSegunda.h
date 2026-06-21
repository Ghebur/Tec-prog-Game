#pragma once
#include "Fase.h"
#include "../Entidades/Personagens/Cobra.h"
#include "../Entidades/Personagens/Shogun.h"
#include "../Entidades/Obstaculos/Espinho.h"
#include <SFML/Graphics.hpp>

namespace Fases {

class FaseSegunda : public Fase {
public:
    FaseSegunda(Mapa1& mapa);
    ~FaseSegunda();
    bool faseFinalizada() const override;
    void verificarTransicaoFase(Personagens::Ninja& jogador);
    Entidades::FlechaShogun* criarProjeteis(sf::Vector2f pos, float dirX) override;

protected:
    void criarInimigos(Mapa1& mapa) override;
    void criarInimigosDificeis(Mapa1& mapa);
    void criarObstaculos(Mapa1& mapa) override;
    void criarFinal(Mapa1& mapa) override;
    //void carregarFase() override;

private:
    Personagens::Shogun* shogunBoss = nullptr;
    Personagens::Shogun* shogunA    = nullptr;
    Personagens::Shogun* shogunB    = nullptr;
    Personagens::Shogun* shogunRand = nullptr;
};

} // namespace Fases
