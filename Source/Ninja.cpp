#include "../Entidades/Personagens/Ninja.h"
#include <SFML/Window/Keyboard.hpp>

Ninja::Ninja(float x, float y) : Personagens(1, 5, 4.5f, 12.f, sf::Vector2f(x, y)) {
    corpo.setSize(sf::Vector2f(tamanho, tamanho/2.0f));
    corpo.setFillColor(sf::Color::Black);
    corpo.setPosition(posicao);
}

Ninja::~Ninja() {}

void Ninja::update() {
    movimentaçao();
    corpo.setPosition(posicao);
}
void Ninja::render(sf::RenderWindow& window) {
    window.draw(corpo);
}

void Ninja::movimentaçao() {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            posicao.y -= velocidade;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            posicao.y += velocidade;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            posicao.x -= velocidade;
        }   
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            posicao.x += velocidade;
        }
}