#pragma once
#include <SFML/Graphics.hpp>
#include "../Listas/Lista_De_Entidades.h"
#include "Entidades/Personagens/Inimigos.h"
#include "Entidades/Obstaculos/Obstaculos.h"
#include "../gerenciadores/Gerenciador_De_Colisao.h"
#include "Entidades/FlechaShogun.h"

namespace Gerenciadores { class Gerenciador_Grafico; }

namespace Fases {

class Fase {
protected:
    Listas::ListaEntidades entidades;
    Gerenciadores::Gerenciador_Colisoes gerenciador;

    virtual void criarInimigos(Mapa1& mapa) = 0;
    void criarPlataformas(Mapa1& mapa);
    virtual void criarObstaculos(Mapa1& mapa) = 0;
    virtual void criarFinal(Mapa1& mapa) = 0;
    void criarInimigosFaceis(Mapa1& mapa);
    void popularGerenciador();

public:
    Fase();
    virtual ~Fase();
    Listas::Lista<Entidades::Entidades>::Elemento<Entidades::Entidades>* getPrimeiroEntidade() {
        return entidades.getPrimeiro();
    }
    void atualizarInimigos(Mapa1& mapa, Personagens::Personagens& jogador);
    void processarObstaculos(Personagens::Ninja& jogador);
    void desenharEntidades(Gerenciadores::Gerenciador_Grafico& gg);
    virtual bool faseFinalizada() const { return false; }
    void salvarFase();
    //virtual void carregarFase() = 0;
    virtual Entidades::FlechaShogun* criarProjeteis(sf::Vector2f pos, float dirX) { return nullptr; }
};

} // namespace Fases
