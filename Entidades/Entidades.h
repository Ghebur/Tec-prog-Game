#pragma once
#include <SFML/Graphics.hpp>
#include "../Ent.h"

class Entidades : public Ent {
protected:
    sf::Vector2f posicao;
    float tamanho;
    std::string buffer;

public:
    Entidades(int id, float tamanho = 12.f, sf::Vector2f pos = {0, 0});
    virtual ~Entidades();
    void salvarDataBuffer();
    virtual void salvar() = 0;
    sf::Vector2f getPos() const;
    float getTamanho() const;
    virtual void desenhar(sf::RenderWindow& window) = 0;
    
};
