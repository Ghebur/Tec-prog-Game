#include <SFML/Graphics.hpp>
#include "../Fases/Fase.h"
#include "../Entidades/Personagens/Cobra.h"
#include "../Entidades/Projetil.h"
#include "../gerenciadores/Gerenciador_Grafico.h"

Fase::Fase() {}

Fase::~Fase() {}

void Fase::criarPlataformas(Mapa1& mapa) {
    const float offset = 125.f;
    const float yChao = 500.f;

    auto garantidas = mapa.getSpawnPoints(5);
    for (size_t i = 0; i < 3 && i < garantidas.size(); i++)
        mapa.adicionarPlataforma(garantidas[i].x - offset, yChao);

    auto opcionais = mapa.getSpawnPoints(7);
    for (auto& pos : opcionais)
        if (rand() % 2)
            mapa.adicionarPlataforma(pos.x - offset, yChao);
}

void Fase::criarInimigosFaceis(Mapa1& mapa) {
    auto spawns = mapa.getSpawnPoints(4);
    if (spawns.size() >= 1) entidades.incluir(new Cobra(spawns[0].x, spawns[0].y));
    if (spawns.size() >= 2) entidades.incluir(new Cobra(spawns[1].x, spawns[1].y));
    if (spawns.size() >= 3) entidades.incluir(new Cobra(spawns[2].x, spawns[2].y));

    auto platSpawns = mapa.getSpawnPoints(5);
    for (auto& pos : platSpawns)
        if (rand() % 2 == 0)
            entidades.incluir(new Cobra(pos.x, 488.f));
}

void Fase::atualizarInimigos(Mapa1& mapa, Personagens& jogador) {
    for (Elemento<Entidades>* e = entidades.getPrimeiro(); e != nullptr; e = e->getProximo()) {
        Inimigo* ini = dynamic_cast<Inimigo*>(e->getInfo());
        if (ini && ini->estaVivo()) {
            ini->update(mapa, jogador);
            Projetil* proj = ini->getProjetilPendente();
            if (proj) {
                entidades.incluir(proj);
                gerenciador.induzirProjetil(proj);
            }
        }
    }
    gerenciador.atualizarProjeteis();
}

void Fase::popularGerenciador() {
    for (Elemento<Entidades>* e = entidades.getPrimeiro(); e != nullptr; e = e->getProximo()) {
        Entidades* ent = e->getInfo();
        if (Inimigo* ini = dynamic_cast<Inimigo*>(ent)) {
            gerenciador.induzirInimigo(ini);
        } else if (Obstaculos* obs = dynamic_cast<Obstaculos*>(ent)) {
            gerenciador.induzirObstaculo(obs);
        } 
        //else if (Projetil* proj = dynamic_cast<Projetil*>(ent)) {
        //  gerenciador.induzirProjetil(proj);
        //}
    }
}

void Fase::processarObstaculos(Ninja& jogador) {
    gerenciador.setJogador(&jogador);
    gerenciador.executar();
}

void Fase::desenharEntidades(Gerenciador_Grafico& gg) {
    for (Elemento<Entidades>* e = entidades.getPrimeiro(); e != nullptr; e = e->getProximo()) {
        Entidades* ent = e->getInfo();
        if (Inimigo* ini = dynamic_cast<Inimigo*>(ent)) {
            if (ini->estaVivo()) gg.desenharEnte(ini);
        } else if (Projetil* proj = dynamic_cast<Projetil*>(ent)) {
            if (!proj->estaMorta()) gg.desenharEnte(proj);
        } else {
            gg.desenharEnte(ent);
        }
    }
}
