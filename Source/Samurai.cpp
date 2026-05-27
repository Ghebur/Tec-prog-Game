#include "../Entidades/Personagens/Samurai.h"

Samurai::Samurai(float x, float y) :
Inimigo(2, 5, {3.f, 0.f}, 12.f, {x, y}, 1),
corpo(sf::Vector2f(12.f, 12.f)),
origemX(x)
{
    corpo.setPosition(posicao);
    corpo.setFillColor(sf::Color::Red);
}

Samurai::~Samurai() {}

void Samurai::movimentaçao() {
    float tempo = relogio.getElapsedTime().asSeconds();
    posicao.x = origemX + std::sin(tempo * velocidade.x) * 100.f;
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

void Samurai::colidirComPersonagem(Personagens& p) {
    if (p.podeReceberDano() && getBounds().findIntersection(p.getBounds())) {
        float dir = (p.getPos().x < getPos().x) ? -1.f : 1.f;
        p.receberKnockback({dir * 700.f, -400.f});
    }
}