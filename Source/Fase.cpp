#include <SFML/Graphics.hpp>
#include "../Listas/Lista.h"
#include "../Fases/Fase.h"
#include "../Entidades/Personagens/Cobra.h"
#include "../Entidades/FlechaShogun.h"
#include "../gerenciadores/Gerenciador_Grafico.h"
#include <fstream>

namespace Fases {

using namespace Personagens;
using namespace Obstaculos;
using namespace Entidades;
using namespace Gerenciadores;
using namespace Listas;

Fase::Fase() {}

Fase::~Fase() {}

void Fase::criarPlataformas(Mapa1& mapa) {
    const float offset = 125.f;
    const float yChao = 500.f;

    auto garantidas = mapa.getSpawnPoints(5);
    for (size_t i = 0; i < 3 && i < garantidas.size(); i++)
        entidades.incluir(new Plataforma(garantidas[i].x - offset, yChao));

    auto opcionais = mapa.getSpawnPoints(7);
    for (auto& pos : opcionais) {
        if (rand() % 2)
            entidades.incluir(new Plataforma(pos.x - offset, yChao));
    }
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

void Fase::atualizarInimigos(Mapa1& mapa, Personagens::Personagens& jogador) {
    for (Lista<Entidades::Entidades>::Elemento<Entidades::Entidades>* e = entidades.getPrimeiro(); e != nullptr; e = e->getProximo()) {
        Inimigo* ini = dynamic_cast<Inimigo*>(e->getInfo());
        if (ini && ini->estaVivo())
            ini->executar(mapa, jogador);
    }
    gerenciador.atualizarProjeteis();
}

void Fase::popularGerenciador() {
    for (Lista<Entidades::Entidades>::Elemento<Entidades::Entidades>* e = entidades.getPrimeiro(); e != nullptr; e = e->getProximo()) {
        Entidades::Entidades* ent = e->getInfo();
        if (Inimigo* ini = dynamic_cast<Inimigo*>(ent)) {
            gerenciador.induzirInimigo(ini);
        } else if (Obstaculos::Obstaculos* obs = dynamic_cast<Obstaculos::Obstaculos*>(ent)) {
            gerenciador.induzirObstaculo(obs);
        }
    }
}

void Fase::processarObstaculos(Ninja& jogador) {
    gerenciador.setJogador(&jogador);
    gerenciador.executar();
}

void Fase::desenharEntidades(Gerenciador_Grafico& gg) {
    for (Lista<Entidades::Entidades>::Elemento<Entidades::Entidades>* e = entidades.getPrimeiro(); e != nullptr; e = e->getProximo()) {
        Entidades::Entidades* ent = e->getInfo();
        if (Inimigo* ini = dynamic_cast<Inimigo*>(ent)) {
            if (ini->estaVivo()) gg.desenharEnte(ini);
        } else if (FlechaShogun* proj = dynamic_cast<FlechaShogun*>(ent)) {
            if (!proj->estaMorta()) gg.desenharEnte(proj);
        } else {
            gg.desenharEnte(ent);
        }
    }
}

int Fase::getQuantidadeInimigosVivos() { // Troque FasePrimeira para o nome da sua classe
    int contagem = 0;
    
    // Pega o primeiro elemento da sua lista
    auto* elementoAtual = getPrimeiroEntidade(); 

    while (elementoAtual != nullptr) {
        Entidades::Entidades* ent = elementoAtual->getInfo();

        if (ent != nullptr) {
            // Tenta converter a Entidade genérica para um Inimigo
            // Se "ent" for um bloco ou o ninja, o resultado será nullptr
            Personagens::Inimigo* inimigo = dynamic_cast<Personagens::Inimigo*>(ent);
            
            // Se a conversão deu certo, significa que é um inimigo!
            if (inimigo != nullptr) {
                if (inimigo->estaVivo()) {
                    contagem++; // Conta +1 inimigo vivo
                }
            }
        }
        
        // Vai para o próximo da lista
        elementoAtual = elementoAtual->getProximo();
    }

    return contagem;
}

void Fase::salvarFase() {
    std::ofstream arquivo("assets/save_ninja.txt", std::ios::trunc);
    arquivo.close();
    arquivo.open("assets/save_samurai.txt", std::ios::trunc);
    arquivo.close();
    arquivo.open("assets/save_cobra.txt", std::ios::trunc);
    arquivo.close();
    arquivo.open("assets/save_espinho.txt", std::ios::trunc);
    arquivo.close();
    arquivo.open("assets/save_shogun.txt", std::ios::trunc);
    arquivo.close();
    arquivo.open("assets/save_oleo.txt", std::ios::trunc);
    arquivo.close();
    arquivo.open("assets/save_plataformas.txt", std::ios::trunc);
    arquivo.close();

    auto* atual = entidades.getPrimeiro();
    while (atual != nullptr) {
        auto* entidade = atual->getInfo();
        if (entidade != nullptr)
            entidade->salvar();
        atual = atual->getProximo();
    }
}

} // namespace Fases
