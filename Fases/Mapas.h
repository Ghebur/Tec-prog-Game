#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Ent.h"
#include "../Entidades/Obstaculos/Plataforma.h"

class Personagens;

class Mapa1 : public Ent {
private:
    static const int LINHAS = 25,
                     COLUNAS = 100;
    float alturaBloco = 50.f;
    float larguraBloco = 50.f;
    int grade[LINHAS][COLUNAS];

    sf::RectangleShape chao;
    sf::Texture texChao;
    sf::Sprite spriteChao{texChao};
    
    // std::vector<Plataforma> plataformas; <-- DELETADO!

public:
    Mapa1();
    void executar() override {}
    void desenhar(sf::RenderWindow& window);
    int getTile(sf::Vector2f pos);
    std::vector<sf::Vector2f> getSpawnPoints(int tile = 4);
    
    // colidirComPersonagens <-- DELETADO!
    // adicionarPlataforma <-- DELETADO!
};