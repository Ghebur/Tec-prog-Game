#include <SFML/Graphics.hpp>
#include "Obstaculos.h"
#pragma once

class oleo:public Obstaculos{
    private:
        sf::Sprite sprite;
        sf::Texture textura;
        float largura;
    public:
        oleo();
        ~oleo();

};