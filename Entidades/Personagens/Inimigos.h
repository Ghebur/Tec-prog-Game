#pragma once
#include "Personagens.h"
#include "../Projetil.h"

class Inimigo : public Personagens {
    protected:
        int nivelDeMaldade;
    public:
        Inimigo(int id, int vida=5, sf::Vector2f velocidade={4.5f, 0.f}, float tamanho=12.f, sf::Vector2f pos={0,0},int nivelDeMaldade=1);
        ~Inimigo();
        int getNivelDeMaldade() const { return nivelDeMaldade; }
        virtual void movimentacao() = 0;
        virtual void danifcar(Personagens& p) = 0;
        virtual void update(Mapa1& mapa, Personagens& p) = 0;
        virtual void desenhar(sf::RenderWindow& window) = 0;
        virtual Projetil* getProjetilPendente() { return nullptr; }
        void colidirComPersonagem(Personagens& p);



};