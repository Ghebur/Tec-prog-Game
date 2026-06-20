#pragma once
#include <SFML/Graphics.hpp>
#include "Personagens.h"

struct Controles {
    sf::Keyboard::Key esquerda = sf::Keyboard::Key::A;
    sf::Keyboard::Key direita  = sf::Keyboard::Key::D;
    sf::Keyboard::Key pular    = sf::Keyboard::Key::W;
    sf::Keyboard::Key lanca    = sf::Keyboard::Key::Space;
};

class Ninja : public Personagens {
    private:
    sf::RectangleShape corpo;

    sf::Texture texIdle;
    sf::Texture texRun;
    sf::Texture texJump;
    sf::Texture texAttack;

    enum class EstadoAnim { IDLE, RUNNING, JUMPING, ATTACKING };
    EstadoAnim estadoAnim = EstadoAnim::IDLE;

    sf::Clock relogioAnim;
    bool olhandoDireita = true;

    static constexpr int FRAME_W = 128;
    static constexpr int FRAME_H = 128;

    enum class EstadoLanca { NORMAL, ARMADO, COOLDOWN };
    EstadoLanca estadoLanca = EstadoLanca::NORMAL;
    sf::Clock relogioLanca;
    bool armado;

    void atualizarAnimacao(bool movendo);

    int pontos;

public:
    Ninja(float x, float y, Controles controles = {}, int pontos = 0);
    ~Ninja();
    void executar(Mapa1& mapa);
    bool movimentacao();
    bool estaArmado() const override { return armado; }
    void tentarRecuperar() override { if (rand() % 3 == 0) ++(*this); }
    sf::FloatRect getBounds() override { return {posicao, corpo.getSize()}; }
    float getTempoParaArmar() const;
    void setPosicao(sf::Vector2f novaPos);
    void salvar() override;
    void adicionarPontos(int valor);
    int getPontos() const;
    Controles controles;
    
};
