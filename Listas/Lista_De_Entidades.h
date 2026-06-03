#pragma once
#include <SFML/Graphics.hpp>
#include "Lista.h"
#include "Entidades/Entidades.h"

class ListaEntidades {
private:
    Lista<Entidades> LEs;

public:
    ListaEntidades() {}

    ~ListaEntidades() {
        for (Elemento<Entidades>* e = LEs.getPrimeiro(); e != nullptr; e = e->getProximo())
            delete e->getInfo();
    }

    void incluir(Entidades* pE) {
        LEs.incluir(pE);
    }

    void percorrer(sf::RenderWindow& window) {
        for (Elemento<Entidades>* e = LEs.getPrimeiro(); e != nullptr; e = e->getProximo())
            e->getInfo()->desenhar(window);
    }

    Elemento<Entidades>* getPrimeiro() const {
        return LEs.getPrimeiro();
    }
};
