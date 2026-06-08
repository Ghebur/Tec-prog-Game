#pragma once
#include "Entidades.h"

class Projetil : public Entidades {
public:
    Projetil(sf::Vector2f pos, float tamanho = 8.f);
    virtual ~Projetil();
    virtual void desenhar(sf::RenderWindow& window) = 0;
};
