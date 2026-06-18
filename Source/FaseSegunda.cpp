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
    shogunBoss = new Shogun(4500.f, 530.f, this);
    entidades.incluir(shogunBoss);
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
