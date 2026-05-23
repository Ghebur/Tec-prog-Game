#pragma once
#include <SFML/Graphics.hpp>
#include "../Entidades.h"

class Personagens:public Entidades{
    protected:  
        int vida;
        sf::Vector2f velocidade;
        bool noChao;
        bool emOleo;
        
    public:
        Personagens(int id, int vida=5,sf::Vector2f velocidade={4.5f, 0.f},float tamanho=12.f,sf::Vector2f pos={0,0});
        ~Personagens();
        virtual void movimentaçao() = 0;
        void aplicarGravidade(float deltaTime);
        void setEmOleo(bool v) { emOleo = v; }
};