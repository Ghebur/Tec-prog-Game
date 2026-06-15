#pragma once
#include "Entidades.h"

class Ninja;

class Projetil : public Entidades {
public:
    Projetil(sf::Vector2f pos, float tamanho = 8.f);
    virtual ~Projetil();
    virtual void desenhar(sf::RenderWindow& window) = 0;
    virtual void executar() override {}
    virtual void update() {}
    virtual void danificar(Ninja& jogador) {}
    virtual bool estaMorta() const { return false; }
    virtual void salvar() override = 0;
};
