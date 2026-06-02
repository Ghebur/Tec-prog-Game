#include "../Entidades/Obstaculos/Espinho.h"


Espinho::Espinho(sf::Vector2f pos, sf::Vector2f tam):
Obstaculos(0, true, tam.x, pos)
{
    forma.setSize(tam);
    forma.setPosition(pos);
    forma.setFillColor(sf::Color(0,0,255));
}
Espinho::~Espinho(){    
}

void Espinho::obstaculizar(Ninja& p){
    sf::FloatRect bounds = forma.getGlobalBounds();
    sf::FloatRect pBounds = {p.getPos(), {p.getTamanho(), p.getTamanho()}};

    if (bounds.findIntersection(pBounds)) {
        p.receberKnockback({300.f,400.f});
        p.perderVida();
    }
}