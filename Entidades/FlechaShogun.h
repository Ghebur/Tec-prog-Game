#pragma once
#include "Projetil.h"
#include <cmath>

class Ninja;

class FlechaShogun : public Projetil {
private:
    sf::RectangleShape forma;   // hitbox
    sf::Texture texFlecha;
    sf::Sprite spriteFlecha{texFlecha};
    sf::Vector2f vel;
    bool morta = false;
    float tempoVoo = 0.f;           // tempo desde spawn (segundos)

    static constexpr float GRAVIDADE       = 500.f;
    static constexpr float DELTA           = 1.f / 60.f;
    static constexpr float PISO_Y          = 550.f;
    static constexpr float SPRITE_W        = 28.f;
    static constexpr float SPRITE_H        = 14.f;
    static constexpr float DELAY_GRAVIDADE = 0.8f;  // segundos em linha reta

public:
    FlechaShogun(sf::Vector2f pos, float velX);
    ~FlechaShogun() override = default;

    void update() override;
    void danificar(Ninja& jogador) override;
    bool estaMorta() const override { return morta; }
    void desenhar(sf::RenderWindow& window) override;
    void executar() override {}
};
