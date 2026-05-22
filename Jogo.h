#pragma once
#include <SFML/Graphics.hpp>
#include "Ent.h"
#include "Entidades/Personagens/Ninja.h"
#include "Fases/Mapas.h"

class Jogo {
    private:
        Ninja ninja;
        Mapa1 mapa1;
        sf::RenderWindow window;
        sf::View camera;
        void ProcessarEventos();
        void Atualizar();
        void Renderizar();


    public:
        Jogo();
        ~Jogo();
        void Rodar(); 
};