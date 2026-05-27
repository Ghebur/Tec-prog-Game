#pragma once
#include <SFML/Graphics.hpp>
#include "Personagens.h"

class Ninja : public Personagens {
    private:
    // embelezar depois
    //sf::Sprite sprite;
    //sf::Texture texture;
    sf::RectangleShape corpo;
public:
    Ninja(float x, float y);
    ~Ninja();
    void update(Mapa1& mapa);
    void desenhar(sf::RenderWindow& window);
    void movimentaçao();
    sf::FloatRect getBounds() override { return {posicao, corpo.getSize()}; }
};