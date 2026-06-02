#pragma once
#include <SFML/Graphics.hpp>
#include "Lista.h"
#include "Entidades/Entidades.h"

class ListaEntidades {
private:
    Lista<Entidades> LEs;

public:
    ListaEntidades() {}
    ~ListaEntidades() {}

    void incluir(Entidades* pE) {
        LEs.incluir(pE);
    }

    void percorrer(sf::RenderWindow& window) {
        Elemento<Entidades>* atual = LEs.getPrimeiro();
        while (atual != nullptr) {
            atual->getInfo()->desenhar(window);
            atual = atual->getProximo();
        }
    }
};
