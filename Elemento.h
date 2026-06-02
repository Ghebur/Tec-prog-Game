#pragma once

template<typename TE>
class Elemento {
private:
    TE* pInfo;
    Elemento<TE>* pProx;

public:
    Elemento(TE* p) : pInfo(p), pProx(nullptr) {}
    ~Elemento() {}

    void setProx(Elemento<TE>* pE) { pProx = pE; }
    Elemento<TE>* getProximo() const { return pProx; }
    TE* getInfo() const { return pInfo; }
};
