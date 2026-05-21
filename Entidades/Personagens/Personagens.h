#include <SFML/Graphics.hpp>
#include "../Ent.h"
#pragma once

class Personagem:public Ent{
    protected:  
        int vida;
    public:
        Personagem();
        ~Personagem();  

};