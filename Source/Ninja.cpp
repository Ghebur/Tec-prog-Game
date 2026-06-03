#include "../Entidades/Personagens/Ninja.h"
#include <SFML/Window/Keyboard.hpp>

#define DELTA_TIME (1.0f / 60.0f) // Supondo 60 FPS

Ninja::Ninja(float x, float y) : Personagens(1, 3, sf::Vector2f(4.5f, 4.5f), 12.f, sf::Vector2f(x, y)) {
    corpo.setSize(sf::Vector2f(tamanho/1.5f, tamanho));
    corpo.setFillColor(sf::Color::White);
    corpo.setPosition({750.0, 550.0});

    lanca.setSize({20.f, 4.f});
    lanca.setFillColor(sf::Color(200, 200, 50));
    armado=false;
}

Ninja::~Ninja() {}

void Ninja::update(Mapa1& mapa) {
    aplicarGravidade(DELTA_TIME);
    verificarColisaoChao(mapa, corpo.getSize().y);
    mapa.colidirComPersonagens(*this);
    movimentaçao();
    corpo.setPosition(posicao);
}
void Ninja::desenhar(sf::RenderWindow& window) {
    window.draw(corpo);
    if (armado)
        window.draw(lanca);
}

void Ninja::movimentaçao() {
    float velX = emOleo ? velocidade.x * 0.4f : velocidade.x;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        posicao.x -= velX;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        posicao.x += velX;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && noChao) {
        velocidade.y = emOleo ? -250.f : -700.f;
        noChao = false;
    }

    float t = relogioLanca.getElapsedTime().asSeconds();
    switch (estadoLanca) {
        case EstadoLanca::NORMAL:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                armado = true;
                estadoLanca = EstadoLanca::ARMADO;
                relogioLanca.restart();
            }
            break;
        case EstadoLanca::ARMADO:
            lanca.setPosition({posicao.x + corpo.getSize().x, posicao.y + 2.f});
            if (t >= 2.f) {
                armado = false;
                estadoLanca = EstadoLanca::COOLDOWN;
                relogioLanca.restart();
            }
            break;
        case EstadoLanca::COOLDOWN:
            if (t >= 4.f)
                estadoLanca = EstadoLanca::NORMAL;
            break;
    }
}

