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
        Gerenciador_Grafico GG;
        sf::Texture texBackground;
        sf::Sprite background{texBackground};
        Ninja ninja;
        std::optional<Ninja> ninja2;
        Mapa1 mapa1;
        sf::View camera;
        FasePrimeira fase1;
        std::optional<FaseSegunda> fase2;
        bool naFase2 = false;
        bool faseTerminada = false;

        sf::Font fonteHUD;
        sf::Text textoVidas;
        sf::Text textoTempo;
        sf::Text textoVidas2;
        sf::Text textoTempo2;

        void ProcessarEventos();
        void Atualizar();
        void Renderizar();

    public:
        Jogo();
        ~Jogo();
        void Rodar();
};
