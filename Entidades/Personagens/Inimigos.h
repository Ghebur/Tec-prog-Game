#pragma once
#include "Personagens.h"

class Inimigo : public Personagens {
    private:
        int nivelDeMaldade;
    public:
        Inimigo(int id, int vida=5, sf::Vector2f velocidade={4.5f, 0.f}, float tamanho=12.f, sf::Vector2f pos={0,0},int nivelDeMaldade=1);
        ~Inimigo();
        int getNivelDeMaldade() const { return nivelDeMaldade; }
        virtual void movimentaçao() = 0;
        virtual void danifcar() = 0;
        void colidirComPersonagem(Personagens& p);



};