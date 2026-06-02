#pragma once
#include <SFML/Graphics.hpp>
#include "Obstaculos.h"
#include "../Entidades/Personagens/Ninja.h"



class Espinho : public Obstaculos{
    private:
        short int danosidade;
        sf::RectangleShape forma;
    public:
    Espinho(sf::Vector2f pos, sf::Vector2f tam);
    ~Espinho();
    void obstaculizar(Ninja& p)override;



};