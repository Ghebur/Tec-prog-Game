#pragma once
#include <SFML/Graphics.hpp>
class Gerenciador_Grafico;

class Ent {
protected:
    int id;
    static Gerenciador_Grafico* pGG;

public:
    Ent(int id = 0);
    virtual ~Ent();
    static void setGG(Gerenciador_Grafico* pG);
    virtual void desenhar(sf::RenderWindow& window) = 0;
};