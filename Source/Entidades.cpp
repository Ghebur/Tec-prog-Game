#include "../Entidades/Entidades.h"

Entidades::Entidades(sf::Vector2f pos):
posicao(pos)
{
}

Entidades::~Entidades()
{
}

sf::Vector2f Entidades::getPos(){return posicao;}