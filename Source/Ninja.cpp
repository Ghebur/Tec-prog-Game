#include "../Entidades/Personagens/Ninja.h"

Ninja::Ninja(float x, float y) : Personagens(1, 5, 4.5f, 12.f) {
    posicao = sf::Vector2f(x, y);
    corpo.setSize(sf::Vector2f(tamanho, tamanho/2.0f));
    corpo.setFillColor(sf::Color::Green);
    corpo.setPosition(posicao);
}