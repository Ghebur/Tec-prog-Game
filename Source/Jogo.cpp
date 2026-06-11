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

    texBackground.loadFromFile("assets/Background/hd.png");
    background.setTexture(texBackground, true);
    background.setScale({800.f / texBackground.getSize().x,
                         600.f / texBackground.getSize().y});
}

Jogo::~Jogo() {}

void Jogo::Atualizar() {
    if (faseTerminada) return;

    sf::Vector2f posCamera = ninja.getPos();
    posCamera.y = 300.f;
    camera.setCenter(posCamera);

    if (!naFase2) {
        fase1.atualizarInimigos(mapa1, ninja);
        if (ninja.estaVivo()) ninja.update(mapa1);
        fase1.processarObstaculos(ninja);
        fase1.verificarTransicaoFase(ninja);

        if (ninja2) {
            if (ninja2->estaVivo()) ninja2->update(mapa1);
            fase1.processarObstaculos(*ninja2);
            fase1.verificarTransicaoFase(*ninja2);
        }

        if (fase1.faseFinalizada()) {
            naFase2 = true;
            fase2.emplace(mapa1);
            ninja.setPosicao({300.f, 400.f});
            if (ninja2) ninja2->setPosicao({350.f, 400.f});
        }
    } else {
        fase2->atualizarInimigos(mapa1, ninja);
        if (ninja.estaVivo()) ninja.update(mapa1);
        fase2->processarObstaculos(ninja);
        fase2->verificarTransicaoFase(ninja);

        if (ninja2) {
            if (ninja2->estaVivo()) ninja2->update(mapa1);
            fase2->processarObstaculos(*ninja2);
            fase2->verificarTransicaoFase(*ninja2);
        }

        if (fase2->faseFinalizada()) faseTerminada = true;
    }
}

void Jogo::Renderizar() {
    sf::RenderWindow& window = GG.getJanela();
    window.clear();
    window.setView(camera);

    background.setPosition(camera.getCenter() - sf::Vector2f(400.f, 300.f));
    window.draw(background);

    GG.desenharEnte(&mapa1);
    if (ninja.estaVivo()) GG.desenharEnte(&ninja);
    if (ninja2 && ninja2->estaVivo()) GG.desenharEnte(&*ninja2);

    if (!naFase2)
        fase1.desenharEntidades(GG);
    else if (fase2)
        fase2->desenharEntidades(GG);

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
    Menu menu;
    ConfigJogo config = menu.executar(GG.getJanela());
    if (config.sair) {
        GG.getJanela().close();
        return;
    }

    if (config.numJogadores >= 2) {
        Controles ctrl2;
        ctrl2.esquerda = sf::Keyboard::Key::Left;
        ctrl2.direita  = sf::Keyboard::Key::Right;
        ctrl2.pular    = sf::Keyboard::Key::Up;
        ctrl2.lanca    = sf::Keyboard::Key::M;
        ninja2.emplace(350.f, 400.f, ctrl2);
    }

    if (config.fase == 2) {
        fase2.emplace(mapa1);
        naFase2 = true;
        if (ninja2) ninja2->setPosicao({350.f, 400.f});
    }

    while (GG.getJanela().isOpen()) {
        ProcessarEventos();
        Atualizar();
        Renderizar();
    }
}
