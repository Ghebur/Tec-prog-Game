#include "../Entidades/Obstaculos/Oleo.h"
#include "../Entidades/Personagens/Personagens.h"

oleo::oleo(sf::Vector2f pos, sf::Vector2f tam) :
    Obstaculos(0, false, tam.y, pos)
{
    forma.setSize(tam);
    forma.setPosition(pos);

    tex.loadFromFile("assets/Oleo/bloco_oleo.png");
    sprite.setTexture(tex, true);
    sprite.setScale({tam.x / tex.getSize().x, tam.y / tex.getSize().y});
    sprite.setPosition(pos);
}

oleo::~oleo() {}

void oleo::obstaculizar(Personagens& p) {
    if (forma.getGlobalBounds().findIntersection(p.getBounds()))
        p.setEmOleo(true);
}

void oleo::desenhar(sf::RenderWindow& window) {
    window.draw(sprite);
}
