#include "../Entidades/Personagens/Cobra.h"
#define DELTA_TIME (1.0f / 60.0f) // Supondo 60 FPS#define

Cobra::Cobra(float x, float y) :
Inimigo(2, 1, {1.5f, 0.f}, 42.f, {x, y}, 1),
corpo(sf::Vector2f(12.f, 12.f)),
origemX(x),
venenosa(rand()%2)
{
    corpo.setPosition(posicao);
    texRun.loadFromFile("assets/CobraAnimacoes/Snake_walk.png");

    sprite.setTexture(texRun, true);
    sprite.setTextureRect(sf::IntRect{{0, 0}, {FRAME_W, FRAME_H}});
    float escala = tamanho / FRAME_H;
    sprite.setScale({escala, escala});
    sprite.setPosition(posicao);
}

Cobra::~Cobra() {}

void Cobra::movimentacao() {
    float velX = emOleo ? velocidade.x * 0.4f : velocidade.x;
    angulo += velX * DELTA_TIME;
    posicao.x = origemX + std::sin(angulo) * 100.f;
    corpo.setPosition(posicao);
    atualizarAnimacao();
}

void Cobra::danifcar(Personagens& p) {
    for(int i =0;i<=nivelDeMaldade;i++)
        p.perderVida();
    if(venenosa)
        p.perderVida();

}

void Cobra::atualizarAnimacao() {
    float escala = (tamanho / FRAME_H);
    int totalFrames = 4;
    sf::Vector2f pos = posicao;
    pos.y = posicao.y - 30.f;

    if (relogioAnim.getElapsedTime().asSeconds() > 0.1f) {
        frameAtual = (frameAtual + 1) % totalFrames;
        relogioAnim.restart();
    }

    bool indoPDireita = std::cos(angulo) > 0;

    sprite.setTextureRect(sf::IntRect{{frameAtual * FRAME_W, 0}, {FRAME_W, FRAME_H}});

    if (indoPDireita) {
        sprite.setScale({-escala, escala});
        sprite.setOrigin({static_cast<float>(FRAME_W), 0.f});
    } else {
        sprite.setScale({escala, escala});
        sprite.setOrigin({0.f, 0.f});
    }

    sprite.setPosition(pos);
}

void Cobra::desenhar(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Cobra::update(Mapa1& mapa, Personagens& p) {
    movimentacao();
    aplicarGravidade(1.f / 60.f);
    verificarColisaoChao(mapa, corpo.getSize().y);
    mapa.colidirComPersonagens(*this);
}
