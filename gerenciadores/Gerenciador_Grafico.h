#pragma once
#include <SFML/Graphics.hpp>
#include "../Ent.h"

class Gerenciador_Grafico{
    private:

    public:
        Gerenciador_Grafico();
        ~Gerenciador_Grafico();
        void desenhar(Ent& e);

};