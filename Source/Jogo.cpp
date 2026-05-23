#include "../Jogo.h"
#include <SFML/Graphics.hpp>

Jogo::Jogo() :
    window(sf::VideoMode({800, 600}), "Meu Jogo UTFPR"),
    ninja(300.f, 400.f),
    mapa1()
{
    window.setFramerateLimit(60);  
    camera.setSize(sf::Vector2f(800.f, 600.f));
}

Jogo::~Jogo() {}

void Jogo::Atualizar(){

    sf::Vector2f posJogador = ninja.getPos();
    posJogador.y = 300;
    camera.setCenter(posJogador);


    
    ninja.update(mapa1);
}

void Jogo::Renderizar() {
    window.clear();
    window.setView(camera);

    mapa1.desenhar(window);
    ninja.desenhar(window); 
    

    window.display();
}
void Jogo::ProcessarEventos() {

    while (const std::optional event = window.pollEvent()) {
        
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }
}

void Jogo::Rodar() {
    while (window.isOpen()) {
        ProcessarEventos();
        Atualizar();
        Renderizar();
    }
}