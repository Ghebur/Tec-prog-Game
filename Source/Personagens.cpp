#include "../Entidades/Personagens/Personagens.h"


Personagens::Personagens(int id, int vida, sf::Vector2f velocidade, float tamanho, sf::Vector2f pos):
Entidades(id, tamanho, pos),
vida(vida),
velocidade(velocidade),
noChao(false),
emOleo(false),
impulso(0.f, 0.f),
framesSemDano(0)
{

}

void Personagens::aplicarGravidade(float deltaTime) {
    const float gravidade = 980.f;
    velocidade.y += gravidade * deltaTime;
    posicao.y   += velocidade.y * deltaTime;
    posicao.x   += impulso.x * deltaTime;
    impulso.x   *= 0.85f;
    if (framesSemDano > 0) framesSemDano--;
}

void Personagens::verificarColisaoChao(Mapa1& mapa, float alturaCorpo) {
    if (posicao.y + alturaCorpo >= 550.f) {
        posicao.y = 550.f - alturaCorpo;
        noChao = true;
        sf::Vector2f pe = {posicao.x + alturaCorpo / 2.f, posicao.y + alturaCorpo + 1.f};
        emOleo = (mapa.getTile(pe) == 2);
    } else {
        noChao = false;
        emOleo = false;
    }
}

void Personagens::receberKnockback(sf::Vector2f forca) {
    impulso.x = forca.x;
    velocidade.y = forca.y;
    noChao = false;
    framesSemDano = 60;
}

Personagens::~Personagens() {}
