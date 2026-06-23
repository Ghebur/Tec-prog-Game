#include <SFML/Graphics.hpp>
#include "../Fases/FaseSegunda.h"
#include "../Entidades/Personagens/Ninja.h"

namespace Fases {

using namespace Personagens;
using namespace Obstaculos;
using namespace Entidades;

FaseSegunda::FaseSegunda(Mapa1& mapa, bool carregar) {
    criarFinal(mapa);
    if (!carregar) {
        criarInimigos(mapa);
        criarPlataformas(mapa);
        criarObstaculos(mapa);
    }
    
    popularGerenciador();
}

FaseSegunda::~FaseSegunda() {}

void FaseSegunda::criarInimigos(Mapa1& mapa) {
    criarInimigosFaceis(mapa);
    criarInimigosDificeis(mapa);
}

void FaseSegunda::criarInimigosDificeis(Mapa1& /*mapa*/) {
    shogunBoss = new Shogun(4500.f, 530.f, this);
    entidades.incluir(shogunBoss);

    shogunA = new Shogun(520.f, 480.f, this);
    entidades.incluir(shogunA);

    shogunB = new Shogun(2820.f, 530.f, this);
    entidades.incluir(shogunB);

    if (rand() % 2) {
        shogunRand = new Shogun(4030.f, 530.f, this);
        entidades.incluir(shogunRand);
    }
}

Entidades::FlechaShogun* FaseSegunda::criarProjeteis(sf::Vector2f pos, float dirX) {
    FlechaShogun* flecha = new FlechaShogun(pos, dirX);
    entidades.incluir(flecha);
    gerenciador.induzirProjetil(flecha);
    return flecha;
}

void FaseSegunda::criarObstaculos(Mapa1& /*mapa*/) {
    entidades.incluir(new Espinho({200.f,  520.f}, {100.f, 30.f}));
    entidades.incluir(new Espinho({1310.f, 520.f}, {100.f, 30.f}));
    entidades.incluir(new Espinho({2100.f, 520.f}, {100.f, 30.f}));
    if (rand() % 2) entidades.incluir(new Espinho({3430.f, 520.f}, {100.f, 30.f}));
    if (rand() % 2) entidades.incluir(new Espinho({4150.f, 520.f}, {100.f, 30.f}));
}

void FaseSegunda::criarFinal(Mapa1& /*mapa*/) {}

bool FaseSegunda::faseFinalizada() const {
    return shogunBoss && !shogunBoss->estaVivo();
}

void FaseSegunda::verificarTransicaoFase(Ninja& /*jogador*/) {}

} // namespace Fases
