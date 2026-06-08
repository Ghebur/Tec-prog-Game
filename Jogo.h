#pragma once
#include "Ent.h"
#include "gerenciadores/Gerenciador_Grafico.h"
#include "Entidades/Personagens/Ninja.h"
#include "Fases/Mapas.h"
#include "Entidades/Obstaculos/Oleo.h"
#include "Fases/FasePrimeira.h"

class Jogo {
    private:
        Gerenciador_Grafico GG;
        Ninja ninja;
        Mapa1 mapa1;
        oleo oleo1{sf::Vector2f(400.f, 500.f)};
        sf::View camera;
        FasePrimeira fase1;
        bool faseTerminada = false;
        void ProcessarEventos();
        void Atualizar();
        void Renderizar();

    public:
        Jogo();
        ~Jogo();
        void Rodar();
};
