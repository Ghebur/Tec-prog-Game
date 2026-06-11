#pragma once
#include "Fase.h"
#include "../Entidades/Personagens/Cobra.h"
#include "../Entidades/Personagens/Shogun.h"
#include "../Entidades/Obstaculos/Espinho.h"
#include <SFML/Graphics.hpp>

class FaseSegunda : public Fase {
public:
    class BlocoFinal : public Entidades {
    private:
        sf::RectangleShape forma;
        bool atingido = false;
    public:
        BlocoFinal(sf::Vector2f pos);
        ~BlocoFinal();
        void passar(Personagens& p);
        void desenhar(sf::RenderWindow& window) override;
        bool foiAtingido() const;
        void executar() override {}
    };

    FaseSegunda(Mapa1& mapa);
    ~FaseSegunda();
    bool faseFinalizada() const override;
    void verificarTransicaoFase(Ninja& jogador);

protected:
    void criarInimigos(Mapa1& mapa) override;
    void criarObstaculos(Mapa1& mapa) override;
    void criarFinal(Mapa1& mapa) override;
    BlocoFinal* blocoFinal = nullptr;
    bool finalizado = false;
};
