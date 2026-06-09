#pragma once
#include <SFML/Graphics.hpp>
#include "../Entidades.h"

class Personagens;

class Obstaculos : public Entidades {
    protected:
        bool danoso;

    public:
        Obstaculos(int id, bool dano, float tamanho, sf::Vector2f pos);
        virtual ~Obstaculos();
        void executar() override {}
        virtual void obstaculizar(Personagens& p) = 0;
        virtual void desenhar(sf::RenderWindow& window) = 0;
};
