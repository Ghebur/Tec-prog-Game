#include "../Entidades/Personagens/Ninja.h"
#include <SFML/Window/Keyboard.hpp>

#define DELTA_TIME (1.0f / 60.0f) // Supondo 60 FPS

Ninja::Ninja(float x, float y) : Personagens(1, 5, sf::Vector2f(4.5f, 4.5f), 12.f, sf::Vector2f(x, y)) {
    corpo.setSize(sf::Vector2f(tamanho/1.5f, tamanho));
    corpo.setFillColor(sf::Color::White);
    corpo.setPosition({750.0, 550.0});
}

Ninja::~Ninja() {}

void Ninja::update(Mapa1& mapa) {
    aplicarGravidade(DELTA_TIME);
    verificarColisaoChao(mapa);
    movimentaçao();
    corpo.setPosition(posicao);
}
void Ninja::desenhar(sf::RenderWindow& window) {
    window.draw(corpo);
}

void Ninja::movimentaçao() {

       

        float velX = emOleo ? velocidade.x * 0.4f : velocidade.x;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            posicao.x -= velX;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            posicao.x += velX;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && noChao) {
            velocidade.y = -500.f;
            noChao = false;
        }


}

void Ninja::verificarColisaoChao(Mapa1& mapa) {
    if (posicao.y + corpo.getSize().y >= 550.f) {
        posicao.y = 550.f - corpo.getSize().y;
        noChao = true;
        sf::Vector2f pe = {posicao.x + corpo.getSize().x / 2.f, posicao.y + corpo.getSize().y + 1.f};
        emOleo = (mapa.getTile(pe) == 2);
    } else {
        noChao = false;
        emOleo = false;
    }
}