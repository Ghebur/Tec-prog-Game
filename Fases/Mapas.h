#pragma once
#include <SFML/Graphics.hpp>
#include "../Ent.h"

class Mapa1:public Ent{
private:
    static const int LINHAS=12,
                     COLUNAS=100;
    float alturaBloco = 50.f;
    float larguraBloco = 50.f;
    int grade[LINHAS][COLUNAS];
    
    sf::RectangleShape chao;
    sf::RectangleShape ceu;


public:
    Mapa1();
    void desenhar(sf::RenderWindow& window);

};