#pragma once
#include <cstdlib>
#include "Fase.h"
#include "../Entidades/Personagens/Samurai.h"
#include "../Entidades/Personagens/Cobra.h"
#include "../Entidades/Obstaculos/BlocoFinal.h"

class FasePrimeira : public Fase {
protected:
    void criarInimigos(Mapa1& mapa) override;
    void criarObstaculos(Mapa1& mapa) override;
    void criarOleo(Mapa1& mapa);
    void criarFinal(Mapa1& mapa) override;
    BlocoFinal* blocoFinal = nullptr;

public:
    FasePrimeira(Mapa1& mapa);
    ~FasePrimeira();
    bool faseFinalizada() const override;
};
