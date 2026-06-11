#include "../Menu.h"
#include <vector>
#include <string>

namespace {
    struct OpcaoMenu {
        std::string texto;
        bool habilitada;
        ConfigJogo config;
    };
}

ConfigJogo Menu::executar(sf::RenderWindow& janela) {
    sf::Font fonte;
    bool carregou = fonte.openFromFile("assets/font.ttf");
    if (!carregou)
        carregou = fonte.openFromFile("C:/Windows/Fonts/arial.ttf");
    if (!carregou)
        return {};

    const std::vector<OpcaoMenu> opcoes = {
        {"Fase 1 - 1 Jogador",               true,  {1, 1, false}},
        {"Fase 1 - 2 Jogadores",             true,  {2, 1, false}},
        {"Fase 2 - 1 Jogador",               true,  {1, 2, false}},
        {"Fase 2 - 2 Jogadores",             true,  {2, 2, false}},
        {"Sair",                             true,  {1, 1, true }},
    };

    int selecao = 0;

    sf::Text titulo(fonte, "NINJA GAME", 64);
    titulo.setFillColor(sf::Color::Yellow);
    {
        sf::FloatRect b = titulo.getLocalBounds();
        titulo.setOrigin({b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f});
        titulo.setPosition({400.f, 130.f});
    }

    sf::Text instrucoes(fonte, "Setas: navegar   |   Enter: selecionar   |   ESC: sair", 17);
    instrucoes.setFillColor(sf::Color(140, 140, 140));
    {
        sf::FloatRect b = instrucoes.getLocalBounds();
        instrucoes.setOrigin({b.position.x + b.size.x / 2.f, 0.f});
        instrucoes.setPosition({400.f, 530.f});
    }

    const float INICIO_Y    = 240.f;
    const float ESPACO_Y    = 52.f;
    const float OPCAO_X     = 180.f;
    const float CURSOR_X    = 140.f;

    std::vector<sf::Text> textos;
    textos.reserve(opcoes.size());
    for (int i = 0; i < (int)opcoes.size(); i++) {
        textos.emplace_back(fonte, opcoes[i].texto, 28);
        textos.back().setPosition({OPCAO_X, INICIO_Y + i * ESPACO_Y});
        textos.back().setFillColor(opcoes[i].habilitada
            ? sf::Color::White
            : sf::Color(90, 90, 90));
    }

    sf::Text cursor(fonte, ">", 28);
    cursor.setFillColor(sf::Color::Yellow);

    while (janela.isOpen()) {
        while (const auto event = janela.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                return {1, 1, true};

            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::Escape)
                    return {1, 1, true};

                if (key->code == sf::Keyboard::Key::Up) {
                    do {
                        selecao = (selecao - 1 + (int)opcoes.size()) % (int)opcoes.size();
                    } while (!opcoes[selecao].habilitada);
                }

                if (key->code == sf::Keyboard::Key::Down) {
                    do {
                        selecao = (selecao + 1) % (int)opcoes.size();
                    } while (!opcoes[selecao].habilitada);
                }

                if (key->code == sf::Keyboard::Key::Enter) {
                    return opcoes[selecao].config;
                }
            }
        }

        cursor.setPosition({CURSOR_X, INICIO_Y + selecao * ESPACO_Y});

        janela.clear(sf::Color(15, 15, 30));
        janela.draw(titulo);
        for (auto& t : textos)
            janela.draw(t);
        janela.draw(cursor);
        janela.draw(instrucoes);
        janela.display();
    }

    return {};
}
