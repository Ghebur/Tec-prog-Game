#include "../Entidades/Obstaculos/Oleo.h"
#include "../Entidades/Personagens/Personagens.h"


oleo::oleo(sf::Vector2f pos, sf::Vector2f tam):
Obstaculos(0, false, tam.x, pos)
{
    forma.setSize(tam);
    forma.setPosition(pos);
    forma.setFillColor(sf::Color(80, 60, 0));
}

oleo::~oleo() {}

void oleo::obstaculizar(Personagens& p) {
    sf::FloatRect bounds = forma.getGlobalBounds();
    sf::FloatRect pBounds = {p.getPos(), {p.getTamanho(), p.getTamanho()}};

    if (bounds.findIntersection(pBounds)) {
        p.setEmOleo(true);
    }
}

void oleo::desenhar(sf::RenderWindow& window) {
    window.draw(forma);
}
