#include "../Entidades/Personagens/Personagens.h"

namespace Personagens {

Personagens::Personagens(int id, int vida, sf::Vector2f velocidade, float tamanho, sf::Vector2f pos):
Entidades(id, tamanho, pos),
vida(vida),
emOleo(false),
frameAtual(0)
{
    this->velocidade = velocidade;
}


void Personagens::verificarColisaoChao(Mapa1& /*mapa*/, float alturaCorpo) {
    if (posicao.y + alturaCorpo >= 550.f) {
        posicao.y = 550.f - alturaCorpo;
        noChao = true;
    } else {
        noChao = false;
        emOleo = false;
    }
}

void Personagens::receberKnockback(sf::Vector2f forca) {
    impulso.x = forca.x;
    velocidade.y = forca.y;
    noChao = false;
    framesSemDano = 45;
}

Personagens::~Personagens() {}

void Personagens::SalvarDataBuffer() {
    Entidades::salvarDataBuffer();
    buffer += " " + std::to_string(vida);
}

void Personagens::setVida(int novaVida) {
    this->vida = novaVida;
}

} // namespace Personagens