#include "../Entidades/Obstaculos/Oleo.h"
#include "../Entidades/Personagens/Personagens.h"
#include <fstream>
#include <cmath>

namespace Obstaculos {

oleo::oleo(sf::Vector2f pos, sf::Vector2f tam) :
    Obstaculos(6, false, tam.y, pos)
{
    larguraTile = tam.x;

    forma.setSize({tam.x * 3.f, tam.y});
    forma.setPosition(pos);

    tex.loadFromFile("assets/Oleo/bloco_oleo.png");
    sprite.setTexture(tex, true);
    sprite.setScale({tam.x / tex.getSize().x, tam.y / tex.getSize().y});

    posBase = {pos.x, pos.y + tam.y};
}

oleo::~oleo() {}

float oleo::variaViscosidade() {
    float t = relogioVisc.getElapsedTime().asSeconds();
    viscosidade = 0.75f + 0.25f * std::sin(t);
    return viscosidade;
}

void oleo::executar() {
    variaViscosidade();
}

void oleo::obstaculizar(Personagens::Personagens& p) {
    executar();
    if (forma.getGlobalBounds().findIntersection(p.getBounds())) {
        p.setEmOleo(true);
        p.setFatorOleo(viscosidade);
    }
}

void oleo::desenhar(sf::RenderWindow& window) {
    for (int i = 0; i < 3; i++) {
        sprite.setPosition({posBase.x + i * larguraTile, posBase.y});
        window.draw(sprite);
    }
}

void oleo::salvar() {
    SalvarDataBuffer();
    buffer = std::to_string(id) + " " + buffer + " " + std::to_string(larguraTile);
    std::ofstream file("assets/save_oleo.txt", std::ios::app);
    if (file.is_open()) {
        file << buffer << "\n";
        file.close();
    }
}

} // namespace Obstaculos
