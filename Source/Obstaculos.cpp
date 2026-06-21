#include "../Entidades/Obstaculos/Obstaculos.h"

namespace Obstaculos {

Obstaculos::Obstaculos(int id, bool dano, float tamanho, sf::Vector2f pos):
Entidades(id, tamanho, pos),
danoso(dano)
{
    noChao = true;
}

Obstaculos::~Obstaculos() {}

void Obstaculos::SalvarDataBuffer() {
    Entidades::salvarDataBuffer();
    buffer += " " + std::to_string(danoso);
}

} // namespace Obstaculos
