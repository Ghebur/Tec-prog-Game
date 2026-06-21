#pragma once
#include <cstdlib>
#include "Fase.h"
#include "../Entidades/Personagens/Samurai.h"
#include "../Entidades/Personagens/Cobra.h"
#include <SFML/Graphics.hpp>

namespace Fases {

class FasePrimeira : public Fase {
public:
    class BlocoFinal : public Entidades::Entidades {
    private:
        sf::RectangleShape forma;
        bool atingido = false;

    public:
        BlocoFinal(sf::Vector2f pos);
        ~BlocoFinal();
        void passar(Personagens::Personagens& p);
        void desenhar(sf::RenderWindow& window) override;
        bool foiAtingido() const;
        void executar() override;
        void salvar() override {}
    };
    FasePrimeira(Mapa1& mapa);
    ~FasePrimeira();
    bool faseFinalizada() const override;
    void verificarTransicaoFase(Personagens::Ninja& jogador);

protected:
    void criarInimigos(Mapa1& mapa) override;
    void criarInimigosMedios(Mapa1& mapa);
    void criarObstaculos(Mapa1& mapa) override;
    void criarOleo(Mapa1& mapa);
    void criarFinal(Mapa1& mapa) override;
    BlocoFinal* blocoFinal = nullptr;
    bool finalizado = false;
    //void carregarFase() override;
};

} // namespace Fases
