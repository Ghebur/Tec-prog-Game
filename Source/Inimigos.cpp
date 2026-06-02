#include "../Entidades/Personagens/Inimigos.h"


Inimigo::Inimigo(int id, int vida, sf::Vector2f velocidade, float tamanho, sf::Vector2f pos, int nivelDeMaldade):
Personagens(id, vida, velocidade, tamanho, pos),
nivelDeMaldade(nivelDeMaldade)
{}

Inimigo::~Inimigo() {}

void Inimigo::colidirComPersonagem(Personagens& p) {
    if (!getBounds().findIntersection(p.getBounds())) return;

    float dir = (p.getPos().x < getPos().x) ? -1.f : 1.f;

    if (p.estaArmado() && podeReceberDano()) {
        perderVida();
        receberKnockback({dir * 600.f, -300.f});
        p.empurrar(-dir * 250.f);
    } else if (!p.estaArmado() && p.podeReceberDano()) {
        p.receberKnockback({dir * 700.f, -400.f});
        p.perderVida();
    }
}
