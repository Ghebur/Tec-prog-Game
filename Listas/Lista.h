#pragma once
#include "Elemento.h"

template<typename TL>
class Lista {
private:
    Elemento<TL>* pPrimeiro;
    Elemento<TL>* pUltimo;

public:
    Lista() : pPrimeiro(nullptr), pUltimo(nullptr) {}
    ~Lista() { limpar(); }

    void incluir(TL* p) {
        Elemento<TL>* novo = new Elemento<TL>(p);
        if (pPrimeiro == nullptr) {
            pPrimeiro = novo;
            pUltimo   = novo;
        } else {
            pUltimo->setProx(novo);
            pUltimo = novo;
        }
    }

    void limpar() {
        Elemento<TL>* atual = pPrimeiro;
        while (atual != nullptr) {
            Elemento<TL>* proximo = atual->getProximo();
            delete atual;
            atual = proximo;
        }
        pPrimeiro = nullptr;
        pUltimo   = nullptr;
    }

    Elemento<TL>* getPrimeiro() const { return pPrimeiro; }
};
