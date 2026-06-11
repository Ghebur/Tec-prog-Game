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
    auto spawns4 = mapa.getSpawnPoints(4);
    auto spawns5 = mapa.getSpawnPoints(5);

    const float yPlatforma = 488.f;

    // Chão: Cobra Cobra Shogun
    if (spawns4.size() >= 1) entidades.incluir(new Cobra(spawns4[0].x, spawns4[0].y));
    if (spawns4.size() >= 2) entidades.incluir(new Cobra(spawns4[1].x, spawns4[1].y));
    if (spawns4.size() >= 3) entidades.incluir(new Shogun(spawns4[2].x, spawns4[2].y));

    for (size_t i = 3; i < spawns4.size(); i++)
        if (rand() % 2)
            entidades.incluir(new Shogun(spawns4[i].x, spawns4[i].y));

    // Plataformas: Cobra Shogun Shogun
    if (spawns5.size() >= 1) entidades.incluir(new Cobra(spawns5[0].x, yPlatforma));
    if (spawns5.size() >= 2) entidades.incluir(new Shogun(spawns5[1].x, yPlatforma));
    if (spawns5.size() >= 3) entidades.incluir(new Shogun(spawns5[2].x, yPlatforma));

    if (spawns5.size() >= 4 && rand() % 2)
        entidades.incluir(new Cobra(spawns5[3].x, yPlatforma));
    if (spawns5.size() >= 5 && rand() % 2)
        entidades.incluir(new Shogun(spawns5[4].x, yPlatforma));
    if (spawns5.size() >= 6 && rand() % 2)
        entidades.incluir(new Cobra(spawns5[5].x, yPlatforma));
}

void FaseSegunda::criarObstaculos(Mapa1& mapa) {
    // Espinhos distribuídos pelo mapa, na altura do chão
    entidades.incluir(new Espinho({800.f,  500.f}, {100.f, 30.f}));
    entidades.incluir(new Espinho({1700.f, 500.f}, {80.f,  30.f}));
    entidades.incluir(new Espinho({2600.f, 500.f}, {120.f, 30.f}));
    entidades.incluir(new Espinho({3400.f, 500.f}, {100.f, 30.f}));
    entidades.incluir(new Espinho({4100.f, 500.f}, {80.f,  30.f}));
}

void FaseSegunda::criarFinal(Mapa1& mapa) {
    blocoFinal = new BlocoFinal({4950.f, 0.f});
    entidades.incluir(blocoFinal);
}

bool FaseSegunda::faseFinalizada() const {
    return finalizado || (blocoFinal && blocoFinal->foiAtingido());
}

void FaseSegunda::verificarTransicaoFase(Ninja& jogador) {
    if (blocoFinal != nullptr)
        blocoFinal->passar(jogador);

    if (!finalizado && blocoFinal && blocoFinal->foiAtingido()) {
        finalizado = true;
        blocoFinal = nullptr;
    }
}

// ── BlocoFinal ──────────────────────────────────────────────────────────────

FaseSegunda::BlocoFinal::BlocoFinal(sf::Vector2f pos) :
    Entidades(99, 20.f, pos)
{
    forma.setSize({20.f, 600.f});
    forma.setPosition(pos);
    forma.setFillColor(sf::Color(0, 220, 80));
}

FaseSegunda::BlocoFinal::~BlocoFinal() {}

void FaseSegunda::BlocoFinal::passar(Personagens& p) {
    if (forma.getGlobalBounds().findIntersection(p.getBounds()))
        atingido = true;
}

void FaseSegunda::BlocoFinal::desenhar(sf::RenderWindow& window) {
    window.draw(forma);
}

bool FaseSegunda::BlocoFinal::foiAtingido() const {
    return atingido;
}
