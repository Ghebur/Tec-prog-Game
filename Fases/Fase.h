#pragma once
#include <SFML/Graphics.hpp>
#include "../Listas/Lista_De_Entidades.h"
#include "Entidades/Personagens/Inimigos.h"
#include "Entidades/Obstaculos/Obstaculos.h"
#include "../gerenciadores/Gerenciador_De_Colisao.h"

class Gerenciador_Grafico;

class Fase {
protected:
    ListaEntidades entidades;
    Gerenciador_Colisoes gerenciador;

    virtual void criarInimigos(Mapa1& mapa) = 0;
    void criarPlataformas(Mapa1& mapa);
    virtual void criarObstaculos(Mapa1& mapa) = 0;
    virtual void criarFinal(Mapa1& mapa) = 0;
    void criarInimigosFaceis(Mapa1& mapa);
    void popularGerenciador();

public:
    Fase();
    virtual ~Fase();
    Lista<Entidades>::Elemento<Entidades>* getPrimeiroEntidade() { 
    return entidades.getPrimeiro(); 
    }
    void atualizarInimigos(Mapa1& mapa, Personagens& jogador);
    void processarObstaculos(Ninja& jogador);
    void desenharEntidades(Gerenciador_Grafico& gg);
    virtual bool faseFinalizada() const { return false; }
    void salvarFase();
};
