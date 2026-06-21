#pragma once
#include <SFML/Graphics.hpp>
#include "../Ent.h"

namespace Entidades {

class Entidades : public Ent {
protected:
    sf::Vector2f posicao;
    float tamanho;
    std::string buffer;
    sf::Vector2f velocidade;
    sf::Vector2f impulso;
    bool noChao;
    int framesSemDano;

public:
    Entidades(int id, float tamanho = 12.f, sf::Vector2f pos = {0, 0});
    virtual ~Entidades();
    void salvarDataBuffer();
    virtual void salvar() = 0;
    sf::Vector2f getPos() const;
    float getTamanho() const;
    void aplicarGravidade(float deltaTime);

};

} // namespace Entidades
