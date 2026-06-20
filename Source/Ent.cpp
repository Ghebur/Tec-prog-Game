#include "../Ent.h"
#include "../Figura.h"

Gerenciador_Grafico* Ent::pGG = nullptr;

Ent::Ent(int id) : id(id) {}

Ent::~Ent() { delete pFig; }

void Ent::setGG(Gerenciador_Grafico* pG) { pGG = pG; }

void Ent::desenhar(sf::RenderWindow& window) {
    if (pFig) pFig->desenhar(window);
}