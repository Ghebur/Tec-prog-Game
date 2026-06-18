#include "../Entidades/Personagens/Ninja.h"
#include <SFML/Window/Keyboard.hpp>
#include <fstream>

#define DELTA_TIME (1.0f / 60.0f)

Ninja::Ninja(float x, float y, Controles controles, int pontos) :
    Personagens(1, 5, sf::Vector2f(4.5f, 4.5f), 50.f, sf::Vector2f(x, y)),
    controles(controles) {
    corpo.setSize(sf::Vector2f(tamanho, tamanho));
    corpo.setFillColor(sf::Color::Transparent);
    corpo.setPosition(posicao);

    armado = false;

    texIdle.loadFromFile("assets/NinjaAnimacoes/Idle.png");
    texRun.loadFromFile("assets/NinjaAnimacoes/Run.png");
    texJump.loadFromFile("assets/NinjaAnimacoes/Jump.png");
    texAttack.loadFromFile("assets/NinjaAnimacoes/Attack_3.png");

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
    else if (armado)
        novoEstado = EstadoAnim::ATTACKING;  // armado sobrepõe Run/Idle no chão
    else if (movendo)
        novoEstado = EstadoAnim::RUNNING;
    else
        novoEstado = EstadoAnim::IDLE;

    if (novoEstado != estadoAnim) {
        estadoAnim = novoEstado;
        frameAtual = 0;
        relogioAnim.restart();
    }

    sf::Texture* tex = &texIdle;
    int totalFrames = 6;
    switch (estadoAnim) {
        case EstadoAnim::IDLE:      tex = &texIdle;   totalFrames = 6;  break;
        case EstadoAnim::RUNNING:   tex = &texRun;    totalFrames = 8;  break;
        case EstadoAnim::JUMPING:   tex = &texJump;   totalFrames = 12; break;
        case EstadoAnim::ATTACKING: tex = &texAttack; totalFrames = 3;  break;
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
}

void Ninja::movimentacao() {
    float velX = emOleo ? velocidade.x * 0.4f : velocidade.x;
    bool moveu = false;

    if (sf::Keyboard::isKeyPressed(controles.esquerda)) {
        posicao.x -= velX;
        olhandoDireita = false;
        moveu = true;
    }
    if (sf::Keyboard::isKeyPressed(controles.direita)) {
        posicao.x += velX;
        olhandoDireita = true;
        moveu = true;
    }
    if (sf::Keyboard::isKeyPressed(controles.pular) && noChao) {
        velocidade.y = emOleo ? -250.f : -500.f;
        noChao = false;
    }

    float t = relogioLanca.getElapsedTime().asSeconds();
    switch (estadoLanca) {
        case EstadoLanca::NORMAL:
            if (sf::Keyboard::isKeyPressed(controles.lanca)) {
                armado = true;
                estadoLanca = EstadoLanca::ARMADO;
                relogioLanca.restart();
            }
            break;
        case EstadoLanca::ARMADO:
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

float Ninja::getTempoParaArmar() const {
    float t = relogioLanca.getElapsedTime().asSeconds();
    if (estadoLanca == EstadoLanca::COOLDOWN)
        return t < 4.f ? 4.f - t : 0.f;
    return 0.f;
}

void Ninja::adicionarPontos(int valor) {
    pontos += valor;
}

int Ninja::getPontos() const {
    return pontos;
}

void Ninja::salvar() {
    SalvarDataBuffer(); 

    buffer += std::to_string(id) + " " + std::to_string(pontos) + "\n";

    std::ofstream arquivo("assets/save_game.txt", std::ios::app);
    if (arquivo.is_open()) {
        arquivo << buffer;
        arquivo.close();
    }
}