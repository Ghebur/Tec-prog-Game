#include "../Entidades/Personagens/Ninja.h"
#include <SFML/Window/Keyboard.hpp>

#define DELTA_TIME (1.0f / 60.0f)

Ninja::Ninja(float x, float y) : Personagens(1, 3, sf::Vector2f(4.5f, 4.5f), 50.f, sf::Vector2f(x, y)) {
    corpo.setSize(sf::Vector2f(tamanho/1.5f, tamanho));
    corpo.setFillColor(sf::Color::Transparent);
    corpo.setPosition(posicao);

    lanca.setSize({20.f, 4.f});
    lanca.setFillColor(sf::Color(200, 200, 50));
    armado = false;

    texIdle.loadFromFile("assets/NinjaAnimacoes/Idle.png");
    texRun.loadFromFile("assets/NinjaAnimacoes/Run.png");
    texJump.loadFromFile("assets/NinjaAnimacoes/Jump.png");

    sprite.setTexture(texIdle, true);
    sprite.setTextureRect(sf::IntRect{{0, 0}, {FRAME_W, FRAME_H}});
    float escala = tamanho / FRAME_H;
    sprite.setScale({escala, escala});
    sprite.setPosition(posicao);
}

Ninja::~Ninja() {}

void Ninja::update(Mapa1& mapa) {
    aplicarGravidade(DELTA_TIME);
    verificarColisaoChao(mapa, corpo.getSize().y);
    mapa.colidirComPersonagens(*this);
    movimentacao();
    corpo.setPosition(posicao);
}

void Ninja::atualizarAnimacao(bool movendo) {
    EstadoAnim novoEstado;
    if (!noChao)
        novoEstado = EstadoAnim::JUMPING;
    else if (movendo)
        novoEstado = EstadoAnim::RUNNING;
    else
        novoEstado = EstadoAnim::IDLE;

    if (novoEstado != estadoAnim) {
        estadoAnim = novoEstado;
        frameAtual = 0;
        relogioAnim.restart();
    }

    int totalFrames = 6;
    sf::Texture* tex = &texIdle;
    switch (estadoAnim) {
        case EstadoAnim::IDLE:    tex = &texIdle; totalFrames = 6;  break;
        case EstadoAnim::RUNNING: tex = &texRun;  totalFrames = 8;  break;
        case EstadoAnim::JUMPING: tex = &texJump; totalFrames = 12; break;
    }

    if (relogioAnim.getElapsedTime().asSeconds() > 0.1f) {
        frameAtual = (frameAtual + 1) % totalFrames;
        relogioAnim.restart();
    }

    float escala = tamanho / FRAME_H;
    sprite.setTexture(*tex);
    sprite.setTextureRect(sf::IntRect{{frameAtual * FRAME_W, 0}, {FRAME_W, FRAME_H}});

    if (olhandoDireita) {
        sprite.setScale({escala, escala});
        sprite.setOrigin({0.f, 0.f});
    } else {
        sprite.setScale({-escala, escala});
        sprite.setOrigin({static_cast<float>(FRAME_W), 0.f});
    }
    sprite.setPosition(posicao);
}

void Ninja::desenhar(sf::RenderWindow& window) {
    window.draw(sprite);
    if (armado)
        window.draw(lanca);
}

void Ninja::movimentacao() {
    float velX = emOleo ? velocidade.x * 0.4f : velocidade.x;
    bool moveu = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        posicao.x -= velX;
        olhandoDireita = false;
        moveu = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        posicao.x += velX;
        olhandoDireita = true;
        moveu = true;
    }
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

    atualizarAnimacao(moveu);
}
void Ninja::setPosicao(sf::Vector2f novaPos) {
    posicao = novaPos; 
    
    corpo.setPosition(posicao); 
}