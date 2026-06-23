#pragma once
#include <SFML/Graphics.hpp>
#include "../Entidades.h"

namespace Personagens { class Personagens; }

namespace Obstaculos {

class Obstaculos : public Entidades::Entidades {
    protected:
        bool danoso;

    public:
        Obstaculos(int id, bool dano, float tamanho, sf::Vector2f pos);
        virtual ~Obstaculos();
        void executar() override {}
        virtual void obstaculizar(Personagens::Personagens& p) = 0;
        virtual void salvar() override = 0;
        void SalvarDataBuffer();
};

} // namespace Obstaculos
