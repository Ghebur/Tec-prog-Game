#pragma once

namespace Listas {

template<typename TL>
class Lista {
public:
    template<typename TE>
    class Elemento {
    private:
        TE* pInfo;
        Elemento<TE>* pProx;

    public:
        Elemento() : pInfo(nullptr), pProx(nullptr) {}
        ~Elemento() {}

        void setProx(Elemento<TE>* pE) { pProx = pE; }
        Elemento<TE>* getProximo() const { return pProx; }
        TE* getInfo() const { return pInfo; }
        void incluir(TE* p) { 
        pInfo = p; 
        }
    };
private:
    Elemento<TL>* pPrimeiro;
    Elemento<TL>* pUltimo;

public:
    Lista() : pPrimeiro(nullptr), pUltimo(nullptr) {}
    ~Lista() { limpar(); }

    void incluir(TL* p) {
        Elemento<TL>* novo = new Elemento<TL>(); 
        
        novo->incluir(p);                        

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

} // namespace Listas
