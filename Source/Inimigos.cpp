#include "../Entidades/Personagens/Inimigos.h"


Inimigo::Inimigo(int id, int vida, sf::Vector2f velocidade, float tamanho, sf::Vector2f pos, int nivelDeMaldade):
Personagens(id, vida, velocidade, tamanho, pos),
nivelDeMaldade(nivelDeMaldade)
{}

Inimigo::~Inimigo() {}
