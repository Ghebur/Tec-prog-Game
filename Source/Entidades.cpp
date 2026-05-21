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

sf::Vector2f Entidades::getPos(){return posicao;}