#pragma once
#include <SFML/Graphics.hpp>
#include "Lista.h"
#include "Entidades/Entidades.h"

namespace Listas {

class ListaEntidades {
private:
    Lista<Entidades::Entidades> LEs;

public:
    ListaEntidades() {}

    ~ListaEntidades() {
        for (Lista<Entidades::Entidades>::Elemento<Entidades::Entidades>* e = LEs.getPrimeiro(); e != nullptr; e = e->getProximo())
            delete e->getInfo();
    }

    void incluir(Entidades::Entidades* pE) {
        LEs.incluir(pE);
    }

    void percorrer(sf::RenderWindow& window) {
        for (Lista<Entidades::Entidades>::Elemento<Entidades::Entidades>* e = LEs.getPrimeiro(); e != nullptr; e = e->getProximo())
            e->getInfo()->desenhar(window);
    }

    Lista<Entidades::Entidades>::Elemento<Entidades::Entidades>* getPrimeiro() const {
        return LEs.getPrimeiro();
    }

    void limpar() {
        LEs.limpar();
    }
};

} // namespace Listas
