#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Ent.h"
#include "../Entidades/Obstaculos/Plataforma.h"

class Personagens;

class Mapa1 : public Ent {
private:
    static const int LINHAS = 12,
                     COLUNAS = 100;
    float alturaBloco = 50.f;
    float larguraBloco = 50.f;
    int grade[LINHAS][COLUNAS];

    sf::RectangleShape chao;
    std::vector<Plataforma> plataformas;

public:
    Mapa1();
    void executar() override {}
    void desenhar(sf::RenderWindow& window);
    int getTile(sf::Vector2f pos);
    void colidirComPersonagens(Personagens& p);
    std::vector<sf::Vector2f> getSpawnPoints(int tile = 4);
    void adicionarPlataforma(float x, float y);
};
