#include <SFML/Graphics.hpp>
#include <random>
#include "../Fases/Fase.h"
#include "../Entidades/Personagens/Cobra.h"

Fase::Fase() {}

Fase::~Fase() {}

void Fase::criarPlataformas(Mapa1& mapa) {
    const float offset = 125.f;

    auto garantidas = mapa.getSpawnPoints(5);
    for (auto& pos : garantidas)
        mapa.adicionarPlataforma(pos.x - offset, pos.y);

    std::mt19937 rng(std::random_device{}());
    std::bernoulli_distribution dist(0.5);
    auto opcionais = mapa.getSpawnPoints(7);
    for (auto& pos : opcionais)
        if (dist(rng))
            mapa.adicionarPlataforma(pos.x - offset, pos.y);
}

void Fase::criarInimigosFaceis(Mapa1& mapa) {
    auto spawns = mapa.getSpawnPoints(4);
    if (spawns.size() >= 1) entidades.incluir(new Cobra(spawns[0].x, spawns[0].y));
    if (spawns.size() >= 2) entidades.incluir(new Cobra(spawns[1].x, spawns[1].y));
    if (spawns.size() >= 3) entidades.incluir(new Cobra(spawns[2].x, spawns[2].y));

    auto platSpawns = mapa.getSpawnPoints(5);
    for (auto& pos : platSpawns)
        if (rand() % 2 == 0)
            entidades.incluir(new Cobra(pos.x, pos.y));
}

void Fase::atualizarInimigos(Mapa1& mapa, Personagens& jogador) {
    for (Elemento<Entidades>* e = entidades.getPrimeiro(); e != nullptr; e = e->getProximo()) {
        Inimigo* ini = dynamic_cast<Inimigo*>(e->getInfo());
        if (ini && ini->estaVivo())
            ini->update(mapa, jogador);
    }
}

void Fase::processarObstaculos(Personagens& jogador) {
    for (Elemento<Entidades>* e = entidades.getPrimeiro(); e != nullptr; e = e->getProximo()) {
        Obstaculos* obs = dynamic_cast<Obstaculos*>(e->getInfo());
        if (obs) obs->obstaculizar(jogador);
    }
}

void Fase::desenharEntidades(sf::RenderWindow& window) {
    for (Elemento<Entidades>* e = entidades.getPrimeiro(); e != nullptr; e = e->getProximo()) {
        Inimigo* ini = dynamic_cast<Inimigo*>(e->getInfo());
        if (ini) {
            if (ini->estaVivo()) ini->desenhar(window);
        } else {
            e->getInfo()->desenhar(window);
        }
    }
}
