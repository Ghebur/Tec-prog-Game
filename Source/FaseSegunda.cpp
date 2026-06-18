#include <SFML/Graphics.hpp>
#include "../Fases/FaseSegunda.h"
#include "../Entidades/Personagens/Ninja.h"

FaseSegunda::FaseSegunda(Mapa1& mapa) {
    criarInimigos(mapa);
    criarPlataformas(mapa);
    criarObstaculos(mapa);
    criarFinal(mapa);
    popularGerenciador();
}

FaseSegunda::~FaseSegunda() {}

void FaseSegunda::criarInimigos(Mapa1& mapa) {
    criarInimigosFaceis(mapa);

    // Boss principal no final do mapa
    shogunBoss = new Shogun(4500.f, 530.f, this);
    entidades.incluir(shogunBoss);

    // Shogun fixo A: sobre a plataforma P1 (x=375-665, topo y=500)
    // corpo 20px → nasce em y=480, oscila 420-620 dentro da plataforma
    shogunA = new Shogun(520.f, 480.f, this);
    entidades.incluir(shogunA);

    // Shogun fixo B: no chão entre P5 opcional (fim 2665) e P3 garantida (início 2975)
    // oscilação 2720-2920, longe dos espinhos em 2100-2200 e 3430-3530
    shogunB = new Shogun(2820.f, 530.f, this);
    entidades.incluir(shogunB);

    // Shogun aleatório: no chão entre P6 opcional (fim 3915) e espinho opcional (início 4150)
    // oscilação 3930-4130, com 50% de chance de aparecer
    if (rand() % 2) {
        shogunRand = new Shogun(4030.f, 530.f, this);
        entidades.incluir(shogunRand);
    }
}

FlechaShogun* FaseSegunda::criarProjeteis(sf::Vector2f pos, float dirX) {
    FlechaShogun* flecha = new FlechaShogun(pos, dirX);
    entidades.incluir(flecha);
    gerenciador.induzirProjetil(flecha);
    return flecha;
}

void FaseSegunda::criarObstaculos(Mapa1& /*mapa*/) {
    // y=520 → base em 550 (nível do chão); posições mínimo 50px longe de qualquer plataforma
    // Plataformas garantidas: 375-725, 1625-1975, 2975-3325
    // Plataformas opcionais:  875-1225, 2375-2725, 3625-3975
    entidades.incluir(new Espinho({200.f,  520.f}, {100.f, 30.f})); // antes da 1ª plataforma
    entidades.incluir(new Espinho({1310.f, 520.f}, {100.f, 30.f})); // entre opt-1 e garantida-2
    entidades.incluir(new Espinho({2100.f, 520.f}, {100.f, 30.f})); // entre garantida-2 e opt-2
     if (rand() % 2)entidades.incluir(new Espinho({3430.f, 520.f}, {100.f, 30.f})); // entre garantida-3 e opt-3
     if (rand() % 2)entidades.incluir(new Espinho({4150.f, 520.f}, {100.f, 30.f})); // após opt-3
}

void FaseSegunda::criarFinal(Mapa1& /*mapa*/) {}

bool FaseSegunda::faseFinalizada() const {
    return shogunBoss && !shogunBoss->estaVivo();
}

void FaseSegunda::verificarTransicaoFase(Ninja& /*jogador*/) {}
