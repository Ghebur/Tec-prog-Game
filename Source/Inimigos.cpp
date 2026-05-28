#include "../Entidades/Personagens/Inimigos.h"


Inimigo::Inimigo(int id, int vida, sf::Vector2f velocidade, float tamanho, sf::Vector2f pos, int nivelDeMaldade):
Personagens(id, vida, velocidade, tamanho, pos),
nivelDeMaldade(nivelDeMaldade)
{}

Inimigo::~Inimigo() {}

void Inimigo::colidirComPersonagem(Personagens& p) {
    if (p.podeReceberDano() && getBounds().findIntersection(p.getBounds())) {
        float dir = (p.getPos().x < getPos().x) ? -1.f : 1.f;
        p.receberKnockback({dir * 700.f, -400.f});
    }
}
