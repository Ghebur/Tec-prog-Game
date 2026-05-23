#include "../Entidades/Obstaculos/Obstaculos.h"

Obstaculos::Obstaculos(int id, bool dano, float tamanho, sf::Vector2f pos):
Entidades(id, tamanho, pos),
danoso(dano)
{}

Obstaculos::~Obstaculos() {}
