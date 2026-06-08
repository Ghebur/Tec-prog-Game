#include "../gerenciadores/Gerenciador_De_Colisao.h"

Gerenciador_Colisoes::Gerenciador_Colisoes() {}

Gerenciador_Colisoes::~Gerenciador_Colisoes() {}

void Gerenciador_Colisoes::setJogador(Ninja* j) {
    log1 = j;
}

bool Gerenciador_Colisoes::verificarColisao(Entidades* pe1, Entidades* pe2) const {
    sf::FloatRect b1{pe1->getPos(), {pe1->getTamanho(), pe1->getTamanho()}};
    sf::FloatRect b2{pe2->getPos(), {pe2->getTamanho(), pe2->getTamanho()}};
    return b1.findIntersection(b2).has_value();
}

void Gerenciador_Colisoes::tratarColisoesJogsObstacs() {
    if (!log1) return;
    for (Obstaculos* obs : LOs)
        obs->obstaculizar(*log1);
}

void Gerenciador_Colisoes::tratarColisoesJogsInimigs() {
    if (!log1) return;
    for (Inimigo* ini : LIs)
        if (ini->estaVivo())
            ini->colidirComPersonagem(*log1);
}

void Gerenciador_Colisoes::tratarColisoesJogsProjeteis() {
    // Projeteis nao implementados ainda
}

void Gerenciador_Colisoes::induzirInimigo(Inimigo* pi) {
    LIs.push_back(pi);
}

void Gerenciador_Colisoes::induzirObstaculo(Obstaculos* po) {
    LOs.push_back(po);
}

void Gerenciador_Colisoes::induzirProjetil(Projetil* ps) {
    LPs.insert(ps);
}

void Gerenciador_Colisoes::executar() {
    tratarColisoesJogsObstacs();
    tratarColisoesJogsInimigs();
    tratarColisoesJogsProjeteis();
}
