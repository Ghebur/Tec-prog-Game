#include "../Entidades/Personagens/Cobra.h"
#define DELTA_TIME (1.0f / 60.0f) // Supondo 60 FPS#define

Cobra::Cobra(float x, float y) :
Inimigo(2, 1, {3.f, 0.f}, 12.f, {x, y}, 1),
corpo(sf::Vector2f(12.f, 12.f)),
origemX(x)
{
    corpo.setPosition(posicao);
    corpo.setFillColor(sf::Color(30, 90, 30));
}

Cobra::~Cobra() {}

void Cobra::movimentaçao() {
    float velX = emOleo ? velocidade.x * 0.4f : velocidade.x;
    float tempo = relogio.getElapsedTime().asSeconds();
    
    posicao.x = origemX + std::sin(tempo * velX) * 100.f;
    corpo.setPosition(posicao);
}

void Cobra::danifcar() {}

void Cobra::desenhar(sf::RenderWindow& window) {
    window.draw(corpo);
}

void Cobra::update(Mapa1& mapa, Personagens& p) {
    movimentaçao();
    aplicarGravidade(1.f / 60.f);
    verificarColisaoChao(mapa, corpo.getSize().y);
    mapa.colidirComPersonagens(*this);
    colidirComPersonagem(p);
}
