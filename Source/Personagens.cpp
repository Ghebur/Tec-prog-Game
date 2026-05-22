#include "../Entidades/Personagens/Personagens.h"


Personagens::Personagens(int id, int vida, sf::Vector2f velocidade, float tamanho, sf::Vector2f pos):
Entidades(id, tamanho, pos),
vida(vida),
velocidade(velocidade),
noChao(false)
{

}

void Personagens::aplicarGravidade(float deltaTime) {
    const float gravidade = 980.f;
    velocidade.y += gravidade * deltaTime;
    posicao.y   += velocidade.y * deltaTime;
}

Personagens::~Personagens() {}
