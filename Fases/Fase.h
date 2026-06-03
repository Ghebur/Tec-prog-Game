#pragma once
#include <SFML/Graphics.hpp>
#include "../Listas/Lista_De_Entidades.h"
#include "Entidades/Personagens/Inimigos.h"
#include "Entidades/Obstaculos/Obstaculos.h"

class Fase {
protected:
    ListaEntidades entidades;

    virtual void criarInimigos(Mapa1& mapa) = 0;
    virtual void criarPlataformas(Mapa1& mapa);
    virtual void criarObstaculos(Mapa1& mapa) = 0;
    void criarInimigosFaceis(Mapa1& mapa);

public:
    Fase();
    virtual ~Fase();

    void atualizarInimigos(Mapa1& mapa, Personagens& jogador);
    void processarObstaculos(Personagens& jogador);
    void desenharEntidades(sf::RenderWindow& window);
};
