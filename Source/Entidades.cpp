#include "../Entidades/Entidades.h"

Entidades::Entidades(int id, float tam, sf::Vector2f pos):
Ent(id),
posicao(pos),
tamanho(tam)
{
}

Entidades::~Entidades()
{
}



sf::Vector2f Entidades::getPos() const { return posicao; }

float Entidades::getTamanho() const { return tamanho; }

void Entidades::salvarDataBuffer() {
    buffer = std::to_string(posicao.x) + " " + std::to_string(posicao.y);
}