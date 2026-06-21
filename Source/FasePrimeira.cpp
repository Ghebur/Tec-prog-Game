#include <SFML/Graphics.hpp>
#include "../Fases/FasePrimeira.h"
#include "../Entidades/Obstaculos/Oleo.h"
#include "../Entidades/Personagens/Ninja.h"
#include <fstream>

namespace Fases {

using namespace Personagens;
using namespace Obstaculos;
using namespace Entidades;

FasePrimeira::FasePrimeira(Mapa1& mapa) {
    criarInimigos(mapa);
    criarPlataformas(mapa);
    criarObstaculos(mapa);
    criarFinal(mapa);
    popularGerenciador();
}

FasePrimeira::~FasePrimeira() {}

void FasePrimeira::criarObstaculos(Mapa1& mapa) {
    criarOleo(mapa);
}

void FasePrimeira::criarOleo(Mapa1& /*mapa*/) {
    entidades.incluir(new oleo({700.f,  500.f}, {50.f, 50.f}));
    entidades.incluir(new oleo({2500.f, 500.f}, {50.f, 50.f}));
    entidades.incluir(new oleo({3250.f, 500.f}, {50.f, 50.f}));

    if (rand() % 2) entidades.incluir(new oleo({1500.f, 500.f}, {50.f, 50.f}));
    if (rand() % 2) entidades.incluir(new oleo({3900.f, 500.f}, {50.f, 50.f}));
    if (rand() % 2) entidades.incluir(new oleo({4300.f, 500.f}, {50.f, 50.f}));
}

void FasePrimeira::criarInimigos(Mapa1& mapa) {
    criarInimigosFaceis(mapa);
    criarInimigosMedios(mapa);
}

void FasePrimeira::criarInimigosMedios(Mapa1& mapa) {
    auto spawns4 = mapa.getSpawnPoints(4);
    auto spawns5 = mapa.getSpawnPoints(5);
    const float yPlatforma = 488.f;

    if (spawns4.size() >= 3) entidades.incluir(new Samurai(spawns4[2].x, spawns4[2].y));
    if (spawns5.size() >= 2) entidades.incluir(new Samurai(spawns5[1].x, yPlatforma));
    if (spawns5.size() >= 3) entidades.incluir(new Samurai(spawns5[2].x, yPlatforma));

    if (spawns4.size() >= 4 && rand() % 2)
        entidades.incluir(new Samurai(spawns4[3].x, spawns4[3].y));
}

void FasePrimeira::criarFinal(Mapa1& mapa) {
    blocoFinal = new BlocoFinal({4950.f, 0.f});
    entidades.incluir(blocoFinal);
}

bool FasePrimeira::faseFinalizada() const {
    return finalizado || (blocoFinal && blocoFinal->foiAtingido());
}

FasePrimeira::BlocoFinal::BlocoFinal(sf::Vector2f pos) :
    Entidades::Entidades(99, 20.f, pos)
{
    forma.setSize({20.f, 600.f});
    forma.setPosition(pos);
    forma.setFillColor(sf::Color(0, 220, 80));
}

FasePrimeira::BlocoFinal::~BlocoFinal() {}

void FasePrimeira::BlocoFinal::passar(Personagens::Personagens& p) {
    if (forma.getGlobalBounds().findIntersection(p.getBounds()))
        atingido = true;
}

void FasePrimeira::BlocoFinal::desenhar(sf::RenderWindow& window) {
    window.draw(forma);
}

bool FasePrimeira::BlocoFinal::foiAtingido() const {
    return atingido;
}

void FasePrimeira::BlocoFinal::executar() {}

void FasePrimeira::verificarTransicaoFase(Ninja& jogador) {
    if (blocoFinal != nullptr)
        blocoFinal->passar(jogador);

    if (!finalizado && blocoFinal && blocoFinal->foiAtingido()) {
        finalizado = true;
        jogador.setPosicao({100.f, 1100.f});
        blocoFinal = nullptr;
    }
}

} // namespace Fases
