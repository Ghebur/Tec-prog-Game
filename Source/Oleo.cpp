#include "../Entidades/Obstaculos/Oleo.h"
#include "../Entidades/Personagens/Personagens.h"
#include <fstream>

oleo::oleo(sf::Vector2f pos, sf::Vector2f tam) :
    Obstaculos(0, false, tam.y, pos)
{
    larguraTile = tam.x;

    // colisão cobre os 3 blocos
    forma.setSize({tam.x * 3.f, tam.y});
    forma.setPosition(pos);

    tex.loadFromFile("assets/Oleo/bloco_oleo.png");
    sprite.setTexture(tex, true);
    sprite.setScale({tam.x / tex.getSize().x, tam.y / tex.getSize().y});

    // sprite desenhado na linha do chão (y+50), sem esticar
    posBase = {pos.x, pos.y + tam.y};
}

oleo::~oleo() {}

void oleo::obstaculizar(Personagens& p) {
    if (forma.getGlobalBounds().findIntersection(p.getBounds()))
        p.setEmOleo(true);
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
    std::ofstream file("assets/save_game.txt", std::ios::app);
    if (file.is_open()) {
        file << buffer << "\n";
        file.close();
    }
}