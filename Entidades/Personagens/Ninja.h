#pragma once
#include <SFML/Graphics.hpp>
#include "Personagens.h"
#include "../Fases/Mapas.h"

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
    void verificarColisaoChao(Mapa1& mapa);
};