#include "../Entidades/Personagens/Shogun.h"
#include "../Fases/Fase.h"
#include "../Figura.h"
#include <cmath>
#include <fstream>

#define DELTA_TIME (1.f / 60.f)

Shogun::Shogun(float x, float y, Fase* fase) :
    Inimigo(4, 7, {3.f, 0.f}, 90.f, {x, y}, 2),
    corpo({20.f, 20.f}),
    fase(fase)
{
    corpo.setPosition(posicao);

    texIdle.loadFromFile("assets/Shogun/Idle.png");
    texRun.loadFromFile("assets/Shogun/Run.png");
    texShot.loadFromFile("assets/Shogun/Shot.png");

    pFig = new Figura(texRun);
    pFig->getSprite().setTextureRect(sf::IntRect{{0, 0}, {FRAME_W, FRAME_H}});
    float escala = tamanho / FRAME_H;
    pFig->getSprite().setScale({escala, escala});
    pFig->getSprite().setPosition(posicao);
}

Shogun::~Shogun() {}

bool Shogun::movimentacao() {
    if (estado == Estado::SHOOTING) return false; // congela posicao durante animacao

    float velX = emOleo ? velocidade.x * 0.4f : velocidade.x;
    angulo += velX * DELTA_TIME;
    posicao.x = origemX + std::sin(angulo) * 100.f;
    corpo.setPosition(posicao);
    return true;
}

void Shogun::danifcar(Personagens& p) {
    for (int i = 0; i <= nivelDeMaldade; i++)
        --p;
}

void Shogun::entrarModoTiro() {
    estado = Estado::SHOOTING;
    frameAtual = 0;
    relogioAnim.restart();
    pFig->getSprite().setTexture(texShot, true);
}

void Shogun::atualizarAnimacao(Personagens& alvo) {
    float escala = tamanho / FRAME_H;
    float secsPerFrame = 0.08f;

    olhandoDireita = (alvo.getPos().x >= posicao.x);

    if (estado != Estado::SHOOTING) {
        // decide estado de movimento
        bool movendo = (estado == Estado::RUNNING);
        sf::Texture* tex = movendo ? &texRun : &texIdle;
        int total = movendo ? FRAMES_RUN : FRAMES_IDLE;

        if (&pFig->getSprite().getTexture() != tex)
            pFig->getSprite().setTexture(*tex, true);

        if (relogioAnim.getElapsedTime().asSeconds() > secsPerFrame) {
            frameAtual = (frameAtual + 1) % total;
            relogioAnim.restart();
        }
    } else {
        // animacao de tiro: avanca frame a frame e nao repete
        if (relogioAnim.getElapsedTime().asSeconds() > secsPerFrame) {
            frameAtual++;
            relogioAnim.restart();
            if (frameAtual >= FRAMES_SHOT) {
                frameAtual = 0;
                estado = Estado::RUNNING;
                pFig->getSprite().setTexture(texRun, true);

                float dirX = olhandoDireita ? 160.f : -160.f;
                sf::Vector2f spawn = {posicao.x, posicao.y + corpo.getSize().y - 30.f};
                if (fase) fase->criarProjeteis(spawn, dirX);
            }
        }
    }

    // aplica frame e espelhamento
    int frameClamp = std::min(frameAtual, FRAMES_SHOT - 1);
    pFig->getSprite().setTextureRect(sf::IntRect{{frameClamp * FRAME_W, 0}, {FRAME_W, FRAME_H}});

    sf::Vector2f pos = {posicao.x, posicao.y - (tamanho - corpo.getSize().y)};
    if (olhandoDireita) {
        pFig->getSprite().setScale({escala, escala});
        pFig->getSprite().setOrigin({0.f, 0.f});
    } else {
        pFig->getSprite().setScale({-escala, escala});
        pFig->getSprite().setOrigin({static_cast<float>(FRAME_W), 0.f});
    }
    pFig->getSprite().setPosition(pos);
}

void Shogun::executar(Mapa1& mapa, Personagens& p) {
    movimentacao();
    aplicarGravidade(DELTA_TIME);
    verificarColisaoChao(mapa, corpo.getSize().y);


    // tenta entrar em modo tiro se estiver em idle/running
    if (estado != Estado::SHOOTING) {
        float dist = std::abs(p.getPos().x - posicao.x);
        if (dist <= DIST_TIRO && relogioTiro.getElapsedTime().asSeconds() >= INTERVALO_TIRO) {
            relogioTiro.restart();
            entrarModoTiro();
        }
    }

    atualizarAnimacao(p);
}

void Shogun::salvar() {
    SalvarDataBuffer();
    buffer += std::to_string(id) + " " + std::to_string(olhandoDireita) + " " +  std::to_string(origemX) + " " +  std::to_string(angulo) + "\n";
    std::ofstream arquivo("assets/save_shogun.txt", std::ios::app);
    if (arquivo.is_open()) {
        arquivo << buffer;
        arquivo.close();
    }
}
