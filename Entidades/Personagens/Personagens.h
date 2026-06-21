#pragma once
#include <SFML/Graphics.hpp>
#include "../Entidades.h"
#include "../../Fases/Mapas.h"

namespace Personagens {

class Personagens : public Entidades::Entidades {
    protected:
        int vida;
        bool emOleo;
        float fatorOleo = 1.f;
        int frameAtual;

    public:
        Personagens(int id, int vida=5,sf::Vector2f velocidade={4.5f, 0.f},float tamanho=12.f,sf::Vector2f pos={0,0});
        ~Personagens();
        void executar() override {}
        virtual bool movimentacao() = 0;
        void verificarColisaoChao(Mapa1& mapa, float alturaCorpo);
        void receberKnockback(sf::Vector2f forca);
        bool podeReceberDano() const { return framesSemDano <= 0; }
        bool estaVivo() const { return vida > 0; }
        Personagens& operator--() { if (vida > 0) vida--; return *this; }
        Personagens& operator++() { if (vida < 4) vida++; return *this; }
        virtual void tentarRecuperar() {}
        int getVida() const { return vida; }
        virtual bool estaArmado() const { return false; }
        void empurrar(float forcaX) { impulso.x = forcaX; }
        virtual sf::FloatRect getBounds() { return {posicao, {tamanho, tamanho}}; }
        void setEmOleo(bool v) { emOleo = v; }
        void setFatorOleo(float f) { fatorOleo = f; }
        float getFatorOleo() const { return fatorOleo; }
        void setPos(sf::Vector2f pos) { posicao = pos; }
        void setNoChao(bool v) { noChao = v; }
        void setVelocidadeY(float vy) { velocidade.y = vy; }
        float getVelocidadeY() const { return velocidade.y; }
        void SalvarDataBuffer();
        virtual void salvar() = 0;
        void setVida(int novaVida);
};

} // namespace Personagens