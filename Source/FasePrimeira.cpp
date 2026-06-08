#include <SFML/Graphics.hpp>
#include <random>
#include "../Fases/FasePrimeira.h"
#include "../Entidades/Obstaculos/Oleo.h"

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

void FasePrimeira::criarOleo(Mapa1& mapa) {
    auto garantidos = mapa.getSpawnPoints(9);
    if (garantidos.size() >= 1) entidades.incluir(new oleo(sf::Vector2f(garantidos[0].x, garantidos[0].y)));
    if (garantidos.size() >= 2) entidades.incluir(new oleo(sf::Vector2f(garantidos[1].x, garantidos[1].y)));
    if (garantidos.size() >= 3) entidades.incluir(new oleo(sf::Vector2f(garantidos[2].x, garantidos[2].y)));

    std::mt19937 rng(std::random_device{}());
    std::bernoulli_distribution dist(0.5);
    auto opcionais = mapa.getSpawnPoints(10);
    for (auto& pos : opcionais)
        if (dist(rng))
            entidades.incluir(new oleo(sf::Vector2f(pos.x, pos.y)));
}

void FasePrimeira::criarInimigos(Mapa1& mapa) {
    auto spawns4 = mapa.getSpawnPoints(4);  // chao: x=1000, 2400, 4000, 4500
    auto spawns5 = mapa.getSpawnPoints(5);  // plataformas: x=500, 1750, 3100(row7) | x=1250, 2250, 3500(row8)

    std::mt19937 rng(std::random_device{}());
    std::bernoulli_distribution dist(0.5);

    // Garantidos no chao: C C S
    if (spawns4.size() >= 1) entidades.incluir(new Cobra(spawns4[0].x, spawns4[0].y));
    if (spawns4.size() >= 2) entidades.incluir(new Cobra(spawns4[1].x, spawns4[1].y));
    if (spawns4.size() >= 3) entidades.incluir(new Samurai(spawns4[2].x, spawns4[2].y));

    // Samurai aleatorio perto do final (tile-4 extras)
    for (size_t i = 3; i < spawns4.size(); i++)
        if (dist(rng))
            entidades.incluir(new Samurai(spawns4[i].x, spawns4[i].y));

    // Garantidos na plataforma: C (3a cobra) S S
    if (spawns5.size() >= 1) entidades.incluir(new Cobra(spawns5[0].x, spawns5[0].y));
    if (spawns5.size() >= 2) entidades.incluir(new Samurai(spawns5[1].x, spawns5[1].y));
    if (spawns5.size() >= 3) entidades.incluir(new Samurai(spawns5[2].x, spawns5[2].y));

    // Cobra aleatoria em plataforma fixa (spawns5[3] = x=1250)
    if (spawns5.size() >= 4 && dist(rng))
        entidades.incluir(new Cobra(spawns5[3].x, spawns5[3].y));

    // Samurai aleatorio em plataforma (spawns5[4] = x=2250)
    if (spawns5.size() >= 5 && dist(rng))
        entidades.incluir(new Samurai(spawns5[4].x, spawns5[4].y));

    // Cobra aleatoria em plataforma fixa (spawns5[5] = x=3500)
    if (spawns5.size() >= 6 && dist(rng))
        entidades.incluir(new Cobra(spawns5[5].x, spawns5[5].y));
}

void FasePrimeira::criarFinal(Mapa1& mapa) {
    blocoFinal = new BlocoFinal({4950.f, 0.f});
    entidades.incluir(blocoFinal);
}

bool FasePrimeira::faseFinalizada() const {
    return blocoFinal && blocoFinal->foiAtingido();
}