#pragma once
#include <cstdlib>
#include "Fase.h"
#include "../Entidades/Personagens/Samurai.h"
#include "../Entidades/Personagens/Cobra.h"

class FasePrimeira : public Fase {
protected:
    void criarInimigos(Mapa1& mapa) override;
    void criarObstaculos(Mapa1& mapa) override;
    void criarOleo(Mapa1& mapa);

public:
    FasePrimeira(Mapa1& mapa);
    ~FasePrimeira();
};
