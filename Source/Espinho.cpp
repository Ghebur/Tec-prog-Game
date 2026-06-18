#include "../Entidades/Obstaculos/Espinho.h"
#include "../Entidades/Personagens/Personagens.h"
#include <fstream>

Espinho::Espinho(sf::Vector2f pos, sf::Vector2f tam) :
    Obstaculos(7, true, tam.x, pos),
    danosidade(1)
{
    forma.setSize(tam);
    forma.setPosition(pos);
    forma.setFillColor(sf::Color::Transparent);

    tex.loadFromFile("assets/Espinho/crystal_lime1.png");
    sprite.setTexture(tex, true);
    sprite.setScale({tam.x / tex.getSize().x, tam.y / tex.getSize().y});
    sprite.setPosition(pos);
}

Espinho::~Espinho() {}

void Espinho::obstaculizar(Personagens& p) {
    if (!forma.getGlobalBounds().findIntersection(p.getBounds())) return;
    if (!p.podeReceberDano()) return;

    float dir = (p.getPos().x < posicao.x) ? -1.f : 1.f;
    p.receberKnockback({dir * 700.f, -400.f});
    p.perderVida();
}

void Espinho::desenhar(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Espinho::salvar() {
    SalvarDataBuffer();
    buffer += " " + std::to_string(id) + " " + std::to_string(danosidade);
    std::ofstream file("save_data.txt", std::ios::app);
    if (file.is_open()) {
        file << "Espinho " << buffer << "\n";
        file.close();
    }
}