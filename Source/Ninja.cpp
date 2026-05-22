#include "../Entidades/Personagens/Ninja.h"
#include <SFML/Window/Keyboard.hpp>

#define DELTA_TIME (1.0f / 60.0f) // Supondo 60 FPS

Ninja::Ninja(float x, float y) : Personagens(1, 5, sf::Vector2f(4.5f, 4.5f), 12.f, sf::Vector2f(x, y)) {
    corpo.setSize(sf::Vector2f(tamanho, tamanho/2.0f));
    corpo.setFillColor(sf::Color::White);
    corpo.setPosition({750.0, 550.0});
}

Ninja::~Ninja() {}

void Ninja::update(Mapa1& mapa) {
    movimentaçao();
    aplicarGravidade(DELTA_TIME); // Supondo 60 FPS
    verificarColisaoChao(mapa);

    corpo.setPosition(posicao);
  
}
void Ninja::desenhar(sf::RenderWindow& window) {
    window.draw(corpo);
}

void Ninja::movimentaçao() {

       

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            posicao.x -= velocidade.x;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            posicao.x += velocidade.x;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && noChao) {
            velocidade.y = -500.f;
            noChao = false;
        }


}

void Ninja::verificarColisaoChao(Mapa1& mapa) {
    // Verificar colisão com o chão
    if (posicao.y + corpo.getSize().y >= 550.f) {
        posicao.y = 550.f - corpo.getSize().y; 
        noChao = true; 
    } else {
        noChao = false; // O personagem está no ar
    }
}