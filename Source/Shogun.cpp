#include "../Entidades/Personagens/Shogun.h"
#include <cmath>

#define DELTA_TIME (1.f / 60.f)

Shogun::Shogun(float x, float y) :
    Inimigo(3, 7, {3.f, 0.f}, 90.f, {x, y}, 2),
    corpo({20.f, 20.f}),
    origemX(x)
{
    corpo.setPosition(posicao);

    texIdle.loadFromFile("assets/Shogun/Idle.png");
    texRun.loadFromFile("assets/Shogun/Run.png");
    texShot.loadFromFile("assets/Shogun/Shot.png");

    sprite.setTexture(texRun, true);
    sprite.setTextureRect(sf::IntRect{{0, 0}, {FRAME_W, FRAME_H}});
    float escala = tamanho / FRAME_H;
    sprite.setScale({escala, escala});
    sprite.setPosition(posicao);
}

Shogun::~Shogun() {}

void Shogun::movimentacao() {
    if (estado == Estado::SHOOTING) return; // congela posicao durante animacao

    float velX = emOleo ? velocidade.x * 0.4f : velocidade.x;
    angulo += velX * DELTA_TIME;
    posicao.x = origemX + std::sin(angulo) * 100.f;
    corpo.setPosition(posicao);
}

void Shogun::danifcar(Personagens& p) {
    for (int i = 0; i <= nivelDeMaldade; i++)
        p.perderVida();
}

void Shogun::entrarModoTiro() {
    estado = Estado::SHOOTING;
    frameAtual = 0;
    relogioAnim.restart();
    sprite.setTexture(texShot, true);
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

        if (&sprite.getTexture() != tex)
            sprite.setTexture(*tex, true);

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
                // animacao concluida: spawna flecha e volta ao RUNNING
                frameAtual = 0;
                estado = Estado::RUNNING;
                sprite.setTexture(texRun, true);

                float dirX = olhandoDireita ? 160.f : -160.f;
                sf::Vector2f spawn = {posicao.x, 500.f};
                projetilPendente = new FlechaShogun(spawn, dirX);
            }
        }
    }

    // aplica frame e espelhamento
    int frameClamp = std::min(frameAtual, FRAMES_SHOT - 1);
    sprite.setTextureRect(sf::IntRect{{frameClamp * FRAME_W, 0}, {FRAME_W, FRAME_H}});

    sf::Vector2f pos = {posicao.x, posicao.y - (tamanho - corpo.getSize().y)};
    if (olhandoDireita) {
        sprite.setScale({escala, escala});
        sprite.setOrigin({0.f, 0.f});
    } else {
        sprite.setScale({-escala, escala});
        sprite.setOrigin({static_cast<float>(FRAME_W), 0.f});
    }
    sprite.setPosition(pos);
}

void Shogun::update(Mapa1& mapa, Personagens& p) {
    movimentacao();
    aplicarGravidade(DELTA_TIME);
    verificarColisaoChao(mapa, corpo.getSize().y);
    mapa.colidirComPersonagens(*this);

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

Projetil* Shogun::getProjetilPendente() {
    Projetil* proj = projetilPendente;
    projetilPendente = nullptr;
    return proj;
}

void Shogun::desenhar(sf::RenderWindow& window) {
    window.draw(sprite);
}
