#include "../Entidades/Obstaculos/BlocoFinal.h"
#include "../Entidades/Personagens/Personagens.h"

BlocoFinal::BlocoFinal(sf::Vector2f pos) :
    Obstaculos(0, false, 20.f, pos)
{
    forma.setSize({20.f, 600.f});
    forma.setPosition(pos);
    forma.setFillColor(sf::Color(0, 220, 80));
}

BlocoFinal::~BlocoFinal() {}

void BlocoFinal::obstaculizar(Personagens& p) {
    if (forma.getGlobalBounds().findIntersection(p.getBounds()))
        atingido = true;
}

void BlocoFinal::desenhar(sf::RenderWindow& window) {
    window.draw(forma);
}

bool BlocoFinal::foiAtingido() const {
    return atingido;
}
