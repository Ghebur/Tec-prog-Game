#include <SFML/Graphics.hpp>
#include "../Ent.h"
#pragma once

class Personagens:public Ent{
    protected:  
        int vida;
        float velocidade;
    public:
        Personagens(int id, int vida=5,float velocidade=4.5f,float tamanho=12.f);
        ~Personagens();  

};