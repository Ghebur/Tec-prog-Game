#pragma once
#include <SFML/Graphics.hpp>
#include "Ent.h"
#include "Entidades/Personagens/Ninja.h"
#include "Fases/Mapas.h"
#include "Entidades/Obstaculos/Oleo.h"
#include "Entidades/Personagens/Samurai.h"

class Jogo {
    private:
        Ninja ninja;
        Mapa1 mapa1;
        oleo oleo1{sf::Vector2f(400.f, 500.f)};
        sf::RenderWindow window;
        sf::View camera;
        Samurai samurai1;
        void ProcessarEventos();
        void Atualizar();
        void Renderizar();


    public:
        Jogo();
        ~Jogo();
        void Rodar(); 
};