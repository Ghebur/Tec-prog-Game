#include "../Entidades/Entidades.h"

namespace Entidades {

Entidades::Entidades(int id, float tam, sf::Vector2f pos):
Ent(id),
posicao(pos),
tamanho(tam),
velocidade({0.f, 0.f}),
impulso({0.f, 0.f}),
noChao(false),
framesSemDano(0)
{
}

void Entidades::aplicarGravidade(float deltaTime) {
    const float gravidade = 980.f;
    velocidade.y += gravidade * deltaTime;
    posicao.y    += velocidade.y * deltaTime;
    posicao.x    += impulso.x * deltaTime;
    impulso.x    *= 0.85f;
    if (framesSemDano > 0) framesSemDano--;
}

Entidades::~Entidades()
{
}



sf::Vector2f Entidades::getPos() const { return posicao; }

float Entidades::getTamanho() const { return tamanho; }

void Entidades::salvarDataBuffer() {
    buffer = std::to_string(posicao.x) + " " + std::to_string(posicao.y);
}

} // namespace Entidades