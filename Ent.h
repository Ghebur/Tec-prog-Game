#pragma once
#include <SFML/Graphics.hpp>
class Gerenciador_Grafico;
class Figura;

class Ent {
protected:
    int id;
    static Gerenciador_Grafico* pGG;
    Figura* pFig = nullptr;

public:
    Ent(int id = 0);
    virtual ~Ent();
    static void setGG(Gerenciador_Grafico* pG);
    virtual void desenhar(sf::RenderWindow& window);
    virtual void executar() = 0;
};