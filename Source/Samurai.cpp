#include "../Entidades/Personagens/Samurai.h"

Samurai::Samurai(float x, float y) :
Inimigo(2, 2, {3.f, 0.f}, 12.f, {x, y}, 1),
corpo(sf::Vector2f(12.f, 12.f)),
origemX(x)
{
    corpo.setPosition(posicao);
    corpo.setFillColor(sf::Color::Red);
}

Samurai::~Samurai() {}

#define DELTA_TIME (1.0f / 60.0f)

void Samurai::movimentaçao() {
    float velX = emOleo ? velocidade.x * 0.4f : velocidade.x;
    angulo += velX * DELTA_TIME;
    posicao.x = origemX + std::sin(angulo) * 100.f;
    corpo.setPosition(posicao);
}

void Samurai::danifcar() {}

void Samurai::desenhar(sf::RenderWindow& window) {
    window.draw(corpo);
}

void Samurai::update(Mapa1& mapa, Personagens& p) {
    movimentaçao();
    aplicarGravidade(1.f / 60.f);
    verificarColisaoChao(mapa, corpo.getSize().y);
    mapa.colidirComPersonagens(*this);
    colidirComPersonagem(p);
}

