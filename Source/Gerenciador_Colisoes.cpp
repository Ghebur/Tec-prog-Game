#include "../gerenciadores/Gerenciador_De_Colisao.h"
#include <vector>

namespace Gerenciadores {

Gerenciador_Colisoes::Gerenciador_Colisoes() {}

Gerenciador_Colisoes::~Gerenciador_Colisoes() {}

void Gerenciador_Colisoes::setJogador(Personagens::Ninja* j) {
    log1 = j;
}

bool Gerenciador_Colisoes::verificarColisao(Entidades::Entidades* pe1, Entidades::Entidades* pe2) const {
    sf::FloatRect b1{pe1->getPos(), {pe1->getTamanho(), pe1->getTamanho()}};
    sf::FloatRect b2{pe2->getPos(), {pe2->getTamanho(), pe2->getTamanho()}};
    return b1.findIntersection(b2).has_value();
}

void Gerenciador_Colisoes::tratarColisoesJogsObstacs() {
    if (!log1) return;
    for (Obstaculos::Obstaculos* obs : LOs)
        obs->obstaculizar(*log1);
}

void Gerenciador_Colisoes::tratarColisoesJogsInimigs() {
    if (!log1) return;
    for (Personagens::Inimigo* ini : LIs) {
        if (ini->estaVivo()) {
            ini->colidirComPersonagem(*log1);
            log1->adicionarPontos(1);
        }
    }
}

void Gerenciador_Colisoes::atualizarProjeteis() {
    std::vector<Entidades::FlechaShogun*> aRemover;
    for (Entidades::FlechaShogun* proj : LPs) {
        proj->executar();
        if (proj->estaMorta()) aRemover.push_back(proj);
    }
    for (Entidades::FlechaShogun* p : aRemover) LPs.erase(p);
}

void Gerenciador_Colisoes::tratarColisoesJogsProjeteis() {
    if (!log1) return;
    for (Entidades::FlechaShogun* proj : LPs)
        proj->danificar(*log1);
}

void Gerenciador_Colisoes::induzirInimigo(Personagens::Inimigo* pi) {
    LIs.push_back(pi);
}

void Gerenciador_Colisoes::induzirObstaculo(Obstaculos::Obstaculos* po) {
    LOs.push_back(po);
}

void Gerenciador_Colisoes::induzirProjetil(Entidades::FlechaShogun* ps) {
    LPs.insert(ps);
}

void Gerenciador_Colisoes::tratarColisoesInimigsObstacs() {
    for (Personagens::Inimigo* ini : LIs) {
        if (ini && ini->estaVivo()) {
            for (Obstaculos::Obstaculos* obs : LOs) {
                obs->obstaculizar(*ini);
            }
        }
    }
}

void Gerenciador_Colisoes::executar() {
    tratarColisoesJogsObstacs();
    tratarColisoesJogsInimigs();
    tratarColisoesJogsProjeteis();
    tratarColisoesInimigsObstacs();
}

} // namespace Gerenciadores
