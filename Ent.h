#pragma once
#include <SFML/Graphics.hpp>
class Gerenciador_Grafico;

class Ent{
    protected:
        int id;
        Gerenciador_Grafico* pGG;
    public:
        Ent(int id=0,Gerenciador_Grafico* pGG = nullptr);
        ~Ent();


};