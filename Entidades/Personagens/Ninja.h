#pragma once
#include <SFML/Graphics.hpp>
#include "Personagens.h"

class Ninja : public Personagens {
    private:
    sf::RectangleShape corpo;
    sf::RectangleShape lanca;

    enum class EstadoLanca { NORMAL, ARMADO, COOLDOWN };
    EstadoLanca estadoLanca = EstadoLanca::NORMAL;
    sf::Clock relogioLanca;
    bool armado = false;

public:
    Ninja(float x, float y);
    ~Ninja();
    void update(Mapa1& mapa);
    void desenhar(sf::RenderWindow& window);
    void movimentaçao();
    bool estaArmado() const override { return armado; }
    sf::FloatRect getBounds() override { return {posicao, corpo.getSize()}; }
};