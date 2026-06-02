#pragma once
#include <cstdlib>
#include "Fase.h"
#include "../Entidades/Personagens/Samurai.h"
#include "../Entidades/Personagens/Cobra.h"

class FasePrimeira : public Fase {
protected:
    void criarInimigos(Mapa1& mapa) override {
        // spawns do chao (sempre aparecem)
        auto spawns = mapa.getSpawnPoints(4);
        if (spawns.size() >= 1) inimigos.incluir(new Cobra(spawns[0].x, spawns[0].y));
        if (spawns.size() >= 2) inimigos.incluir(new Samurai(spawns[1].x, spawns[1].y));
        if (spawns.size() >= 3) inimigos.incluir(new Cobra(spawns[2].x, spawns[2].y));
        


        // spawns de plataforma (50% de chance cada)
        auto platSpawns = mapa.getSpawnPoints(5);
        for (auto& pos : platSpawns)
            if (rand() % 2 == 0)
                inimigos.incluir(new Cobra(pos.x, pos.y));
    }

    void criarPlataformas(Mapa1& mapa) override {
        // plataformas gerenciadas pelo Mapa1 por enquanto
    }

public:
    FasePrimeira(Mapa1& mapa) {
        criarInimigos(mapa);
        criarPlataformas(mapa);
    }
    ~FasePrimeira() {}
};
