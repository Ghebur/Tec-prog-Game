#pragma once
#include <SFML/Graphics.hpp>
#include "Personagens.h"

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
    int frameAtual = 0;
    sf::Clock relogioAnim;
    bool olhandoDireita = true;

    static constexpr int FRAME_W = 128;
    static constexpr int FRAME_H = 128;

    enum class EstadoLanca { NORMAL, ARMADO, COOLDOWN };
    EstadoLanca estadoLanca = EstadoLanca::NORMAL;
    sf::Clock relogioLanca;
    bool armado;

    void atualizarAnimacao(bool movendo);

public:
    Ninja(float x, float y);
    ~Ninja();
    void update(Mapa1& mapa);
    void desenhar(sf::RenderWindow& window);
    void movimentaçao();
    bool estaArmado() const override { return armado; }
    sf::FloatRect getBounds() override { return {posicao, corpo.getSize()}; }
};
