#pragma once
#include <SFML/Graphics.hpp>
namespace Gerenciadores { class Gerenciador_Grafico; }
class Figura;

class Ent {
protected:
    int id;
    static Gerenciadores::Gerenciador_Grafico* pGG;
    Figura* pFig = nullptr;

public:
    Ent(int id = 0);
    virtual ~Ent();
    static void setGG(Gerenciadores::Gerenciador_Grafico* pG);
    virtual void desenhar(sf::RenderWindow& window);
    virtual void executar() = 0;
};