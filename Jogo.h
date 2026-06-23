#pragma once
#include <optional>
#include "Ent.h"
#include "Menu.h"
#include "gerenciadores/Gerenciador_Grafico.h"
#include "Entidades/Personagens/Ninja.h"
#include "Fases/Mapas.h"
#include "Entidades/Obstaculos/Oleo.h"
#include "Fases/FasePrimeira.h"
#include "Fases/FaseSegunda.h"

class Jogo {
    private:
        bool pausado{false};
        sf::Text textoPausa;
        void salvarJogo();
        Gerenciadores::Gerenciador_Grafico GG;
        sf::Texture texBackground;
        sf::Sprite background{texBackground};
        Personagens::Ninja ninja;
        std::optional<Personagens::Ninja> ninja2;
        Mapa1 mapa1;
        sf::View camera;
        Fases::FasePrimeira fase1;
        std::optional<Fases::FaseSegunda> fase2;
        bool naFase2 = false;
        bool faseTerminada = false;
        bool gameOver = false;
        bool vitoria{false};
        std::string nomeP1{""};
        std::string nomeP2{""};
        bool digitandoP2{false}; 
        

        sf::Font fonteHUD;
        sf::Text textoVidas;
        sf::Text textoTempo;
        sf::Text textoVidas2;
        sf::Text textoTempo2;
        sf::Text textoPontos;
        sf::Text textoPontos2;
        sf::Text textoVitoria;

        void ProcessarEventos();
        void Atualizar();
        void Renderizar();
        void salvarRanking();
        
    

    public:
        Jogo();
        ~Jogo();
        void Rodar();
        void carregarEntidades(Fases::Fase* faseAtual);
};
