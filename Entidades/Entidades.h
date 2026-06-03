#pragma once
#include <SFML/Graphics.hpp>
#include "../Ent.h"

class Entidades : public Ent {
protected:
    sf::Vector2f posicao;
    float tamanho;

public:
    Entidades(int id, float tamanho = 12.f, sf::Vector2f pos = {0, 0});
    virtual ~Entidades();
    sf::Vector2f getPos();
    float getTamanho();
    virtual void desenhar(sf::RenderWindow& window) = 0;
};
