#include <SFML/Graphics.hpp>
#include "../Ent.h"
#pragma once

class Obstaculos:public Ent{
    protected:  
        bool danoso;
    public:
        Obstaculos(bool dano = false);
        ~Obstaculos();  

};