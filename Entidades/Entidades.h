#include <SFML/Graphics.hpp>
#pragma once

class Entidades{
    protected:
        sf::Vector2f posicao;
        //TODO: ver 0oq é o buffer e tals
    public:
        Entidades(sf::Vector2f pos ={0,0});
        virtual ~Entidades();
        sf::Vector2f getPos();
        virtual void executar() = 0;
        virtual void desenhar() = 0;
};