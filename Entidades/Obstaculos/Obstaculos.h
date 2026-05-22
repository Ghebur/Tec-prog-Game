#pragma once
#include <SFML/Graphics.hpp>
#include "../Ent.h"

class Obstaculos:public Ent{
    protected:  
        bool danoso;
    public:
        Obstaculos(bool dano = false);
        ~Obstaculos();  

};