#include "../Jogo.h"

Jogo::Jogo() :
    GG(sf::VideoMode({800, 600}), "Meu Jogo UTFPR"),
    ninja(300.f, 400.f),
    mapa1(),
    fase1(mapa1)
{
    GG.getJanela().setFramerateLimit(60);
    camera.setSize(sf::Vector2f(800.f, 600.f));
    Ent::setGG(&GG);
}

Jogo::~Jogo() {}

void Jogo::Atualizar() {
    if (faseTerminada) return;

    sf::Vector2f posJogador = ninja.getPos();
    posJogador.y = 300.f;
    camera.setCenter(posJogador);

    fase1.atualizarInimigos(mapa1, ninja);
    if (ninja.estaVivo()) ninja.update(mapa1);
    fase1.processarObstaculos(ninja);

    if (fase1.faseFinalizada()) faseTerminada = true;
}

void Jogo::Renderizar() {
    sf::RenderWindow& window = GG.getJanela();
    window.clear();
    window.setView(camera);

    GG.desenharEnte(&mapa1);
    if (ninja.estaVivo()) GG.desenharEnte(&ninja);
    fase1.desenharEntidades(GG);

    if (faseTerminada) {
        sf::RectangleShape overlay({800.f, 600.f});
        overlay.setPosition(camera.getCenter() - sf::Vector2f(400.f, 300.f));
        overlay.setFillColor(sf::Color(0, 180, 60, 160));
        window.draw(overlay);
    }

    window.display();
}

void Jogo::ProcessarEventos() {
    while (const std::optional event = GG.getJanela().pollEvent()) {
        if (event->is<sf::Event::Closed>())
            GG.getJanela().close();
    }
}

void Jogo::Rodar() {
    while (GG.getJanela().isOpen()) {
        ProcessarEventos();
        Atualizar();
        Renderizar();
    }
}
