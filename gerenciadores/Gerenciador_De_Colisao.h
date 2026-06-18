#pragma once
#include <vector>
#include <list>
#include <set>
#include "Entidades/Entidades.h"
#include "Entidades/Personagens/Inimigos.h"
#include "Entidades/Obstaculos/Obstaculos.h"
#include "Entidades/FlechaShogun.h"
#include "Entidades/Personagens/Ninja.h"

class Gerenciador_Colisoes {
private:
    std::vector<Inimigo*>   LIs;
    std::list<Obstaculos*>  LOs;
    std::set<FlechaShogun*> LPs;
    Ninja*                  log1 = nullptr;

public:
    Gerenciador_Colisoes();
    ~Gerenciador_Colisoes();

    void tratarColisoesInimigsObstacs();
    void setJogador(Ninja* j);
    bool verificarColisao(Entidades* pe1, Entidades* pe2) const;
    void tratarColisoesJogsObstacs();
    void tratarColisoesJogsInimigs();
    void tratarColisoesJogsProjeteis();
    void induzirInimigo(Inimigo* pi);
    void induzirObstaculo(Obstaculos* po);
    void induzirProjetil(FlechaShogun* ps);
    void atualizarProjeteis();
    void executar();
};