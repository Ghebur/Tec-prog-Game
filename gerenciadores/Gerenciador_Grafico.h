#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../Ent.h"

class Gerenciador_Grafico {
private:
    sf::RenderWindow janela;

public:
    Gerenciador_Grafico(sf::VideoMode modo, const std::string& titulo);
    ~Gerenciador_Grafico();

    void desenharEnte(Ent* pE);
    sf::RenderWindow& getJanela();
};
