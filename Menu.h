#pragma once
#include <SFML/Graphics.hpp>

struct ConfigJogo {
    int numJogadores = 1;
    int fase = 1;
    bool sair = false;
};

class Menu {
public:
    ConfigJogo executar(sf::RenderWindow& janela);
};
