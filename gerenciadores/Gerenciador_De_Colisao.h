#pragma once
#include <vector>
#include <list>
#include <set>
#include "Entidades/Entidades.h"
#include "Entidades/Personagens/Inimigos.h"
#include "Entidades/Obstaculos/Obstaculos.h"
#include "Entidades/FlechaShogun.h"
#include "Entidades/Personagens/Ninja.h"

namespace Gerenciadores {

class Gerenciador_Colisoes {
private:
    std::vector<Personagens::Inimigo*>    LIs;
    std::list<Obstaculos::Obstaculos*>    LOs;
    std::set<Entidades::FlechaShogun*>    LPs;
    Personagens::Ninja*                   log1 = nullptr;

public:
    Gerenciador_Colisoes();
    ~Gerenciador_Colisoes();

    void tratarColisoesInimigsObstacs();
    void setJogador(Personagens::Ninja* j);
    bool verificarColisao(Entidades::Entidades* pe1, Entidades::Entidades* pe2) const;
    void tratarColisoesJogsObstacs();
    void tratarColisoesJogsInimigs();
    void tratarColisoesJogsProjeteis();
    void induzirInimigo(Personagens::Inimigo* pi);
    void induzirObstaculo(Obstaculos::Obstaculos* po);
    void induzirProjetil(Entidades::FlechaShogun* ps);
    void atualizarProjeteis();
    void executar();
    void limpar();
};

} // namespace Gerenciadores