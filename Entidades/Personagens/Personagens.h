#include <SFML/Graphics.hpp>
#include "../Entidades/Entidades.h"
#pragma once

class Personagens:public Entidades{
    protected:  
        int vida;
        float velocidade;
        
    public:
        Personagens(int id, int vida=5,float velocidade=4.5f,float tamanho=12.f,sf::Vector2f pos={0,0});
        ~Personagens();  
        virtual void movimentaçao() = 0;
};