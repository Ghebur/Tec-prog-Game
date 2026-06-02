#pragma once
#include <SFML/Graphics.hpp>
#include "Listas/Lista.h"
#include "Entidades/Personagens/Inimigos.h"

class Fase {
protected:
    Lista<Inimigo> inimigos;

    virtual void criarInimigos(Mapa1& mapa) = 0;
    virtual void criarPlataformas(Mapa1& mapa) = 0;

public:
    Fase() {}
    virtual ~Fase() {
        for (Elemento<Inimigo>* e = inimigos.getPrimeiro(); e != nullptr; e = e->getProximo())
            delete e->getInfo();
    }

    void atualizarInimigos(Mapa1& mapa, Personagens& jogador) {
        for (Elemento<Inimigo>* e = inimigos.getPrimeiro(); e != nullptr; e = e->getProximo())
            if (e->getInfo()->estaVivo())
                e->getInfo()->update(mapa, jogador);
    }

    void desenharInimigos(sf::RenderWindow& window) {
        for (Elemento<Inimigo>* e = inimigos.getPrimeiro(); e != nullptr; e = e->getProximo())
            if (e->getInfo()->estaVivo())
                e->getInfo()->desenhar(window);
    }
};
