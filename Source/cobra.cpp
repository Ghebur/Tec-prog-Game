#include "../Entidades/Personagens/Cobra.h"
#include "../Figura.h"
#include <fstream>
#define DELTA_TIME (1.0f / 60.0f) // Supondo 60 FPS#define

Cobra::Cobra(float x, float y) :
Inimigo(2, 1, {1.5f, 0.f}, 42.f, {x, y}, 1),
corpo(sf::Vector2f(12.f, 12.f)),
venenosa(rand()%2)
{
    corpo.setPosition(posicao);
    texRun.loadFromFile("assets/CobraAnimacoes/Snake_walk.png");

    pFig = new Figura(texRun);
    pFig->getSprite().setTextureRect(sf::IntRect{{0, 0}, {FRAME_W, FRAME_H}});
    float escala = tamanho / FRAME_H;
    pFig->getSprite().setScale({escala, escala});
    pFig->getSprite().setPosition(posicao);
}

Cobra::~Cobra() {}

void Cobra::danifcar(Personagens& p) {
    for(int i =0;i<=nivelDeMaldade;i++)
        --p;
    if(venenosa)
        --p;

}

void Cobra::atualizarAnimacao() {
    float escala = (tamanho / FRAME_H);
    int totalFrames = 4;
    sf::Vector2f pos = posicao;
    pos.y = posicao.y - 29.f;

    if (relogioAnim.getElapsedTime().asSeconds() > 0.1f) {
        frameAtual = (frameAtual + 1) % totalFrames;
        relogioAnim.restart();
    }

    bool indoPDireita = std::cos(angulo) > 0;

    pFig->getSprite().setTextureRect(sf::IntRect{{frameAtual * FRAME_W, 0}, {FRAME_W, FRAME_H}});

    if (indoPDireita) {
        pFig->getSprite().setScale({-escala, escala});
        pFig->getSprite().setOrigin({static_cast<float>(FRAME_W), 0.f});
    } else {
        pFig->getSprite().setScale({escala, escala});
        pFig->getSprite().setOrigin({0.f, 0.f});
    }

    pFig->getSprite().setPosition(pos);
}

void Cobra::executar(Mapa1& mapa, Personagens& p) {
    movimentacao();
    aplicarGravidade(1.f / 60.f);
    verificarColisaoChao(mapa, corpo.getSize().y);
}

void Cobra::salvar() {
    salvarDataBuffer(); 

    buffer = std::to_string(id) + " " + buffer + std::to_string(venenosa) + " " + std::to_string(origemX) + " " + std::to_string(angulo) + "\n";
    
    std::ofstream arquivo("assets/save_cobra.txt", std::ios::app);
    if (arquivo.is_open()) {
        arquivo << buffer;
        arquivo.close();
    }
}

void Cobra::setVenenosa(int v) {
    this->venenosa = v;
}

void Cobra::setAngulo(float a) {
    this->angulo = a;
}