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
    sf::RectangleShape lanca;

    sf::Texture texIdle;
    sf::Texture texRun;
    sf::Texture texJump;
    sf::Sprite sprite{texIdle};

    enum class EstadoAnim { IDLE, RUNNING, JUMPING };
    EstadoAnim estadoAnim = EstadoAnim::IDLE;

    sf::Clock relogioAnim;
    bool olhandoDireita = true;

    static constexpr int FRAME_W = 128;
    static constexpr int FRAME_H = 128;

    enum class EstadoLanca { NORMAL, ARMADO, COOLDOWN };
    EstadoLanca estadoLanca = EstadoLanca::NORMAL;
    sf::Clock relogioLanca;
    bool armado;

    Controles controles;

    void atualizarAnimacao(bool movendo);

public:
    Ninja(float x, float y, Controles controles = {});
    ~Ninja();
    void update(Mapa1& mapa);
    void desenhar(sf::RenderWindow& window);
    void movimentacao();
    bool estaArmado() const override { return armado; }
    sf::FloatRect getBounds() override { return {posicao, corpo.getSize()}; }
    float getTempoParaArmar() const;
    void setPosicao(sf::Vector2f novaPos);
};
