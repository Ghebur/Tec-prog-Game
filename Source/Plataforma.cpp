#include "../Entidades/Obstaculos/Plataforma.h"
#include "../Entidades/Personagens/Personagens.h"
#include "../Entidades/Personagens/Ninja.h"
#include <fstream>

namespace Obstaculos {

Plataforma::Plataforma(float x, float y) :
Obstaculos(5, false, 0.f, sf::Vector2f(x, y))
{
    plataforma.setSize(sf::Vector2f(290.f, 50.f));
    plataforma.setPosition(sf::Vector2f(x + 30.f, y));

    textura.loadFromFile("assets/Plataforma/ice_rock4.png");
    sprite.setTexture(textura, true);
    sprite.setScale({350.f / textura.getSize().x, 50.f / textura.getSize().y});
    sprite.setPosition(sf::Vector2f(x, y));
}

Plataforma::Plataforma(const Plataforma& other) :
Obstaculos(other),
plataforma(other.plataforma),
textura(other.textura)
{
    sprite.setTexture(textura, true);
    sprite.setScale(other.sprite.getScale());
    sprite.setPosition(other.sprite.getPosition());
}

Plataforma::~Plataforma() {}

void Plataforma::desenhar(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Plataforma::obstaculizar(Personagens::Personagens& p) {
    sf::FloatRect pb = plataforma.getGlobalBounds();
    sf::FloatRect cb = p.getBounds();

    auto intersection = pb.findIntersection(cb);
    if (!intersection) return;

    float overlapX = intersection->size.x;
    float overlapY = intersection->size.y;
    float vy = p.getVelocidadeY();

    float persoCenterY = cb.position.y + cb.size.y / 2.f;
    float platCenterY = pb.position.y + pb.size.y / 2.f;

    if (vy < 0.f && persoCenterY <= platCenterY) {
        return;
    }

    if (overlapY < overlapX) {
        if (persoCenterY <= platCenterY && vy >= 0.f) {
            p.setPos({p.getPos().x, pb.position.y - cb.size.y});
            p.setVelocidadeY(0.f);
            p.setNoChao(true);
            return;
        }
        if (persoCenterY > platCenterY && vy < 0.f) {
            p.setPos({p.getPos().x, pb.position.y + pb.size.y});
            p.setVelocidadeY(0.f);
            return;
        }
    } else {
        float persoCenterX = cb.position.x + cb.size.x / 2.f;
        float platCenterX = pb.position.x + pb.size.x / 2.f;

        if (persoCenterX < platCenterX) {
            p.setPos({pb.position.x - cb.size.x, p.getPos().y});
        } else {
            p.setPos({pb.position.x + pb.size.x, p.getPos().y});
        }
    }
}

void Plataforma::salvar() {
    SalvarDataBuffer();
    std::ofstream file("assets/save_plataformas.txt", std::ios::app);
    if (file.is_open()) {
        file << buffer << "\n";
        file.close();
    }
}

} // namespace Obstaculos
