#include "../Entidades/FlechaShogun.h"
#include "../Entidades/Personagens/Ninja.h"
#include "../Figura.h"
#include <cmath>
#include <fstream>

namespace Entidades {

FlechaShogun::FlechaShogun(sf::Vector2f pos, float velX) :
    Entidades(0, 14.f, pos),
    vel(velX * 1.8f, 0.f)
{
    forma.setSize({SPRITE_W, SPRITE_H});
    forma.setOrigin({SPRITE_W / 2.f, SPRITE_H / 2.f});
    forma.setFillColor(sf::Color::Transparent);
    forma.setPosition(pos);

    texFlecha.loadFromFile("assets/Flecha/Arrow.png");
    pFig = new Figura(texFlecha);
    pFig->getSprite().setScale({SPRITE_W / texFlecha.getSize().x,
                                SPRITE_H / texFlecha.getSize().y});
    pFig->getSprite().setOrigin({SPRITE_W / 2.f, SPRITE_H / 2.f});
    pFig->getSprite().setPosition(pos);
}

bool FlechaShogun::estaMorta() const {
    return morta;
}

void FlechaShogun::executar() {
    tempoVoo += DELTA;

    if (tempoVoo > DELAY_GRAVIDADE)
        vel.y += GRAVIDADE * DELTA;

    posicao += vel * DELTA;

    float ang = (tempoVoo > DELAY_GRAVIDADE)
                ? std::atan2(vel.y, vel.x)
                : (vel.x >= 0.f ? 0.f : static_cast<float>(M_PI));
    pFig->getSprite().setRotation(sf::radians(ang));
    pFig->getSprite().setPosition(posicao);
    forma.setRotation(sf::radians(ang));
    forma.setPosition(posicao);

    if (posicao.y >= PISO_Y)
        morta = true;
}

void FlechaShogun::danificar(Personagens::Ninja& jogador) {
    if (morta) return;
    if (forma.getGlobalBounds().findIntersection(jogador.getBounds()) &&
        jogador.podeReceberDano()) {
        --jogador;
        morta = true;
    }
}

void FlechaShogun::salvar() {}

} // namespace Entidades
