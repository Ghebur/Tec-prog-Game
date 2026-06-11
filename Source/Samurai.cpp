#include "../Entidades/Personagens/Samurai.h"

Samurai::Samurai(float x, float y) :
Inimigo(2, 2, {3.f, 0.f}, 50.f, {x, y}, 1),
corpo(sf::Vector2f(12.f, 12.f)),
origemX(x),
graduacao(rand()%3+1)
{
    vida = graduacao;
    corpo.setPosition(posicao);
    //corpo.setFillColor(sf::Color::Red);
    texRun.loadFromFile("assets/SamuraiAnimacoes/Run.png");

    sprite.setTexture(texRun, true);
    sprite.setTextureRect(sf::IntRect{{0, 0}, {FRAME_W, FRAME_H}});
    float escala = tamanho / FRAME_H;
    sprite.setScale({escala, escala});
    sprite.setPosition(posicao);
}

Samurai::~Samurai() {}

#define DELTA_TIME (1.0f / 60.0f)

void Samurai::movimentacao() {
    float velX = emOleo ? velocidade.x * 0.4f : velocidade.x;
    angulo += velX * DELTA_TIME;
    posicao.x = origemX + std::sin(angulo) * 100.f;
    corpo.setPosition(posicao);
    atualizarAnimacao();
}

void Samurai::danifcar(Personagens& p) {
    for(int i =0;i<=nivelDeMaldade;i++)
        p.perderVida();
    
}

void Samurai::desenhar(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Samurai::update(Mapa1& mapa, Personagens& p) {
    movimentacao();
    aplicarGravidade(1.f / 60.f);
    verificarColisaoChao(mapa, corpo.getSize().y);
    mapa.colidirComPersonagens(*this);
}

void Samurai::atualizarAnimacao(){
    float escala = (tamanho / FRAME_H);
    int totalFrames = 8;
    sf::Vector2f pos = posicao;

    pos.y = posicao.y - 38.f;

    if (relogioAnim.getElapsedTime().asSeconds() > 0.1f) {
        frameAtual = (frameAtual + 1) % totalFrames;
        relogioAnim.restart();
    }

    bool indoPDireita = std::cos(angulo) > 0;
    
    sprite.setTextureRect(sf::IntRect{{frameAtual * FRAME_W, 0}, {FRAME_W, FRAME_H}});

    if(!indoPDireita){
        sprite.setScale({-escala, escala});
        sprite.setOrigin({static_cast<float>(FRAME_W), 0.f});
    }
    else{
        sprite.setScale({escala, escala});
        sprite.setOrigin({0.f, 0.f});
    }
    
    sprite.setPosition(pos);
}

