#include "../Entidades/Personagens/Personagens.h"


Personagens::Personagens(int id, int vida, float velocidade, float tamanho, sf::Vector2f pos):
Entidades(id, tamanho, pos),
vida(vida),
velocidade(velocidade)
{}

Personagens::~Personagens() {}
