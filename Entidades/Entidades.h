#pragma once
#include <SFML/Graphics.hpp>
#include "../Ent.h"

class Entidades:public Ent{
    protected:
        sf::Vector2f posicao;
        float tamanho;
        //TODO: ver 0oq é o buffer e tals
    public:
        Entidades(int id, float tamanho=12.f,sf::Vector2f pos ={0,0});
        ~Entidades();
        sf::Vector2f getPos();
        float getTamanho();
        //virtual void executar()=0;
        //virtual void salvar()=0;

};