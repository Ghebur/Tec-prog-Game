#include "../Entidades/Obstaculos/Oleo.h"
#include "../Entidades/Personagens/Personagens.h"

oleo::oleo(sf::Vector2f pos, sf::Vector2f tam) :
    Obstaculos(0, false, tam.y, pos)
{
    forma.setSize(tam);
    forma.setPosition(pos);
    forma.setFillColor(sf::Color(80, 60, 0));
}

oleo::~oleo() {}

void oleo::obstaculizar(Personagens& p) {
    if (forma.getGlobalBounds().findIntersection(p.getBounds()))
        p.setEmOleo(true);
}

void oleo::desenhar(sf::RenderWindow& window) {
    window.draw(forma);
}
