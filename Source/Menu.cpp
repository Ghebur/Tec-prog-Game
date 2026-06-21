#include "../Menu.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

namespace {
    struct OpcaoMenu {
        std::string texto;
        bool habilitada;
        ConfigJogo config;
        bool abreRanking; // <-- Adicionamos isso para identificar o botão do Ranking
    };

    struct RegistroRanking {
        std::string nome;
        int pontos;
    };
}

ConfigJogo Menu::executar(sf::RenderWindow& janela) {
    sf::Font fonte;
    bool carregou = fonte.openFromFile("assets/font.ttf");
    if (!carregou)
        carregou = fonte.openFromFile("C:/Windows/Fonts/arial.ttf");
    if (!carregou)
        return {};

    // Adicionamos a opção "Ranking" na lista
    const std::vector<OpcaoMenu> opcoes = {
        {"Fase 1 - 1 Jogador",     true,  {1, 1, false}, false},
        {"Fase 1 - 2 Jogadores",   true,  {2, 1, false}, false},
        {"Fase 2 - 1 Jogador",     true,  {1, 2, false}, false},
        {"Fase 2 - 2 Jogadores",   true,  {2, 2, false}, false},
        {"Ranking",                true,  {1, 1, false}, true }, // <- Ativa a tela de Ranking!
        {"Sair",                   true,  {1, 1, true }, false},
    };

    int selecao = 0;
    bool mostrandoRanking = false; // Controla qual tela estamos vendo

    // --- CONFIGURAÇÃO TEXTOS MENU ---
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

    // --- CONFIGURAÇÃO TEXTO RANKING ---
    sf::Text textoRanking(fonte, "", 30);
    textoRanking.setFillColor(sf::Color::White);

    // Função local (lambda) para carregar e formatar o ranking quando precisarmos
    auto carregarRanking = [&]() {
        std::vector<RegistroRanking> placares;
        std::ifstream arquivo("assets/ranking.txt");
        
        if (arquivo.is_open()) {
            std::string linha, nome;
            int pontos;
            while (std::getline(arquivo, linha)) {
                std::stringstream ss(linha);
                if (ss >> nome >> pontos) {
                    placares.push_back({nome, pontos});
                }
            }
            arquivo.close();
        }

        std::sort(placares.begin(), placares.end(), [](const RegistroRanking& a, const RegistroRanking& b) {
            return a.pontos > b.pontos;
        });

        std::string textoFinal = "=== MELHORES NINJAS ===\n\n";
        int limite = std::min((int)placares.size(), 10);
        for (int i = 0; i < limite; ++i) {
            textoFinal += std::to_string(i + 1) + ". " + placares[i].nome + " -> " + 
                          std::to_string(placares[i].pontos) + " pts\n";
        }
        if (placares.empty()) {
            textoFinal += "Nenhum ninja registrado ainda!\n";
        }
        
        textoFinal += "\n\n[ ESC ] Voltar ao Menu";
        textoRanking.setString(textoFinal);
        
        sf::FloatRect b = textoRanking.getLocalBounds();
        textoRanking.setOrigin({b.size.x / 2.f, b.size.y / 2.f});
        textoRanking.setPosition({400.f, 300.f}); // Centralizado na tela 800x600
    };

    // --- LOOP PRINCIPAL DO MENU ---
    while (janela.isOpen()) {
        while (const auto event = janela.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                return {1, 1, true};

            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                
                // SE A TELA DE RANKING ESTIVER ABERTA
                if (mostrandoRanking) {
                    if (key->code == sf::Keyboard::Key::Escape) {
                        mostrandoRanking = false; // Fecha o ranking e volta pro menu
                    }
                } 
                // SE O MENU NORMAL ESTIVER ABERTO
                else {
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
                        // Se for a opção de Ranking, carrega o txt e muda a tela
                        if (opcoes[selecao].abreRanking) {
                            carregarRanking();
                            mostrandoRanking = true;
                        } else {
                            // Se for qualquer outra opção (Jogar ou Sair), retorna o config normal
                            return opcoes[selecao].config;
                        }
                    }
                }
            }
        }

        janela.clear(sf::Color(15, 15, 30));

        if (mostrandoRanking) {
            // Desenha apenas o Ranking
            janela.draw(textoRanking);
        } else {
            // Desenha o Menu Normal
            cursor.setPosition({CURSOR_X, INICIO_Y + selecao * ESPACO_Y});
            janela.draw(titulo);
            for (auto& t : textos)
                janela.draw(t);
            janela.draw(cursor);
            janela.draw(instrucoes);
        }

        janela.display();
    }

    return {};
}