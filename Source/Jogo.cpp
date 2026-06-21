#include <cmath>
#include "../Jogo.h"
#include <fstream>
#include <iostream>

using namespace Personagens;
using namespace Fases;

Jogo::Jogo() :
    GG(sf::VideoMode({800, 600}), "Meu Jogo UTFPR"),
    ninja(300.f, 400.f),
    mapa1(),
    fase1(mapa1),
    textoPausa(fonteHUD),
    textoVidas(fonteHUD),
    textoTempo(fonteHUD),
    textoVidas2(fonteHUD),
    textoTempo2(fonteHUD),
    textoPontos(fonteHUD),
    textoPontos2(fonteHUD),
    textoVitoria(fonteHUD)
{
    GG.getJanela().setFramerateLimit(60);
    camera.setSize(sf::Vector2f(800.f, 600.f));
    Ent::setGG(&GG);

    if (!texBackground.loadFromFile("assets/Background/hd.png")) {
        // fallback loading can be handled here if needed
    }
    background.setTexture(texBackground, true);
    background.setScale({800.f / texBackground.getSize().x,
                         600.f / texBackground.getSize().y});

    bool carregouFonte = fonteHUD.openFromFile("assets/font.ttf");
    if (!carregouFonte)
        carregouFonte = fonteHUD.openFromFile("C:/Windows/Fonts/arial.ttf");

    if (carregouFonte) {
        textoVidas.setFont(fonteHUD);
        textoVidas.setCharacterSize(22);
        textoVidas.setFillColor(sf::Color::Black);
        textoVidas.setPosition({20.f, 20.f});

        textoTempo.setFont(fonteHUD);
        textoTempo.setCharacterSize(22);
        textoTempo.setFillColor(sf::Color::Black);
        textoTempo.setPosition({20.f, 50.f});

        textoVidas2.setFont(fonteHUD);
        textoVidas2.setCharacterSize(22);
        textoVidas2.setFillColor(sf::Color::Black);
        textoVidas2.setPosition({525.f, 20.f});

        textoTempo2.setFont(fonteHUD);
        textoTempo2.setCharacterSize(22);
        textoTempo2.setFillColor(sf::Color::Black);
        textoTempo2.setPosition({525.f, 50.f});

        textoPontos.setFont(fonteHUD);
        textoPontos.setCharacterSize(22);
        textoPontos.setFillColor(sf::Color::Black);
        textoPontos.setPosition({20.f, 80.f});

        textoPontos2.setFont(fonteHUD);
        textoPontos2.setCharacterSize(22);
        textoPontos2.setFillColor(sf::Color::Black);
        textoPontos2.setPosition({525.f, 80.f});
    }
}

Jogo::~Jogo() {}

void Jogo::Atualizar() {
    if (!ninja.estaVivo() && (!ninja2 || !ninja2->estaVivo())) {
        gameOver = true;
    }

    if (gameOver || faseTerminada) return;

    if (faseTerminada) return;

    sf::Vector2f posCamera = ninja.getPos();
    posCamera.y = 300.f;
    camera.setCenter(posCamera);

    if (pausado) return; 

    if (!naFase2) {
        fase1.atualizarInimigos(mapa1, ninja);
        if (ninja.estaVivo()) ninja.executar(mapa1);
        ninja.setEmOleo(false);
        fase1.processarObstaculos(ninja);
        fase1.verificarTransicaoFase(ninja);

        if (ninja2) {
            if (ninja2->estaVivo()) ninja2->executar(mapa1);
            ninja2->setEmOleo(false);
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
        if (ninja.estaVivo()) ninja.executar(mapa1);
        ninja.setEmOleo(false);
        fase2->processarObstaculos(ninja);
        fase2->verificarTransicaoFase(ninja);

        if (ninja2) {
            if (ninja2->estaVivo()) ninja2->executar(mapa1);
            ninja2->setEmOleo(false);
            fase2->processarObstaculos(*ninja2);
            fase2->verificarTransicaoFase(*ninja2);
        }

        if (fase2->faseFinalizada()) faseTerminada = true;

        if (naFase2 && fase2->getQuantidadeInimigosVivos() == 0) {
    vitoria = true;
}
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

    // Menu visual de Pausa
    if (pausado) {
        sf::RectangleShape overlay({800.f, 600.f});
        overlay.setPosition(camera.getCenter() - sf::Vector2f(400.f, 300.f));
        overlay.setFillColor(sf::Color(0, 0, 0, 160));
        window.draw(overlay);

        textoPausa.setFont(fonteHUD);
        textoPausa.setString("JOGO PAUSADO\n\n[P] Retornar ao Jogo\n[S] Salvar Jogada");
        textoPausa.setCharacterSize(32);
        textoPausa.setFillColor(sf::Color::White);
        
        sf::FloatRect bounds = textoPausa.getLocalBounds();
        textoPausa.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
        textoPausa.setPosition(camera.getCenter());
        
        window.draw(textoPausa);
    }

    if (faseTerminada) {
        sf::RectangleShape overlay({800.f, 600.f});
        overlay.setPosition(camera.getCenter() - sf::Vector2f(400.f, 300.f));
        overlay.setFillColor(sf::Color(0, 180, 60, 160));
        window.draw(overlay);
    }

    // --- CORREÇÃO DO GAME OVER (Desenha ANTES de resetar a View para a HUD estática!) ---
    if (gameOver) {
        sf::RectangleShape overlay({800.f, 600.f});
        overlay.setPosition(camera.getCenter() - sf::Vector2f(400.f, 300.f));
        overlay.setFillColor(sf::Color(180, 0, 0, 160)); // Filtro Vermelho
        window.draw(overlay);

        textoPausa.setFont(fonteHUD);
        textoPausa.setString("VOCE MORREU!\n\n[N] Reiniciar\n[Fechar Janela] Sair");
        textoPausa.setCharacterSize(32);
        textoPausa.setFillColor(sf::Color::White);
        
        sf::FloatRect bounds = textoPausa.getLocalBounds();
        textoPausa.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
        textoPausa.setPosition(camera.getCenter()); // Agora centraliza perfeitamente no meio da tela do jogo!
        
        window.draw(textoPausa);
    }

    if (vitoria) {
        sf::RectangleShape overlay({800.f, 600.f});
        overlay.setPosition(camera.getCenter() - sf::Vector2f(400.f, 300.f));
        overlay.setFillColor(sf::Color(218, 165, 32, 200)); // Amarelo Dourado Transparente
        window.draw(overlay);

        textoVitoria.setFont(fonteHUD);
        textoVitoria.setCharacterSize(30);
        textoVitoria.setFillColor(sf::Color::White);

        // Monta o texto dinâmico mostrando os pontos e o que o cara tá digitando
        std::string texto = "VITORIA!\nTodos os inimigos foram derrotados!\n\n";
        texto += "Pontos P1: " + std::to_string(ninja.getPontos()) + "\nNome P1: " + nomeP1;
        if (!digitandoP2) texto += "_"; // Simula um cursor piscando pro P1
        
        if (ninja2) {
            texto += "\n\nPontos P2: " + std::to_string(ninja2->getPontos()) + "\nNome P2: " + nomeP2;
            if (digitandoP2) texto += "_"; // Cursor muda pro P2
        }

        texto += "\n\n[ENTER] para Confirmar";

        textoVitoria.setString(texto);
        
        // Centraliza perfeito na tela
        sf::FloatRect bounds = textoVitoria.getLocalBounds();
        textoVitoria.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
        textoVitoria.setPosition(camera.getCenter());
        
        window.draw(textoVitoria);
    }

    // Retorna para a visualização padrão fixada na janela para renderizar a HUD estática
    window.setView(window.getDefaultView());
    
    textoVidas.setString("Vidas: " + std::to_string(ninja.getVida()));
    float tempoArmar = ninja.getTempoParaArmar();
    std::string tempoArmarTexto = tempoArmar > 0.f
        ? std::to_string(static_cast<int>(std::ceil(tempoArmar))) + "s"
        : "Pronto";
    textoTempo.setString("Tempo p/ armar: " + tempoArmarTexto);
    textoPontos.setString("Pontos: " + std::to_string(ninja.getPontos()));
    window.draw(textoVidas);
    window.draw(textoTempo);
    window.draw(textoPontos);

    if (ninja2) {
        textoVidas2.setString("P2 Vidas: " + std::to_string(ninja2->getVida()));
        float tempoArmar2 = ninja2->getTempoParaArmar();
        std::string tempoArmar2Texto = tempoArmar2 > 0.f
            ? std::to_string(static_cast<int>(std::ceil(tempoArmar2))) + "s"
            : "Pronto";
        textoTempo2.setString("P2 Tempo p/ armar: " + tempoArmar2Texto);
        textoPontos2.setString("P2 Pontos: " + std::to_string(ninja2->getPontos()));
        window.draw(textoVidas2);
        window.draw(textoTempo2);
        window.draw(textoPontos2);
    }

    window.display();
}
void Jogo::ProcessarEventos() {
    while (const std::optional event = GG.getJanela().pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            GG.getJanela().close();
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            
            if (keyPressed->code == sf::Keyboard::Key::P) {
                pausado = !pausado;
            }

            if (pausado && keyPressed->code == sf::Keyboard::Key::S) {
                salvarJogo();
            }

            // --- CORREÇÃO DO BOTÃO N (Só fecha a janela do loop principal para voltar pro loop do Rodar()) ---
            if (gameOver && keyPressed->code == sf::Keyboard::Key::N) {
                gameOver = false;
                ninja.ressuscitar(); 
                if (ninja2) ninja2->ressuscitar();
                
                // Em vez de chamar Rodar(), nós apenas fechamos a janela interna do loop secundário.
                // Mas como o loop principal do Rodar() usa isOpen(), vamos quebrar o loop secundário limpando as fases ou saindo do loop de jogo!
                return; 
            }
        }
        if (const auto* textEvent = event->getIf<sf::Event::TextEntered>()) {
            if (vitoria) {
                char32_t unicode = textEvent->unicode;
                
                // Escolhe qual string estamos editando (P1 ou P2)
                std::string& nomeAtual = digitandoP2 ? nomeP2 : nomeP1;

                if (unicode == '\b' || unicode == 8) { // Se apertou Backspace
                    if (!nomeAtual.empty()) nomeAtual.pop_back();
                } 
                else if (unicode == '\r' || unicode == '\n') { // Se apertou Enter
                    if (ninja2 && !digitandoP2) {
                        // Se tem jogador 2 e o P1 já deu Enter, passa a vez pro P2
                        digitandoP2 = true;
                    } else {
                        // Se for só 1 jogador ou o P2 já deu Enter, finaliza!
                        salvarRanking();
                        vitoria = false;
                        nomeP1 = ""; // Limpa pra próxima partida
                        nomeP2 = "";
                        digitandoP2 = false;
                        return; // Quebra o loop para voltar pro Menu (igual no GameOver)
                    }
                } 
                else if (unicode < 128 && nomeAtual.size() < 10) { 
                    // Aceita letras normais e limita a 10 caracteres
                    nomeAtual += static_cast<char>(unicode);
                }
            }
        }
    }
}

void Jogo::Rodar() {
    // Colocamos um while externo. Sempre que o jogo terminar ou voltar pro menu, ele reinicia aqui sem estourar a memória!
    while (GG.getJanela().isOpen()) {
        Menu menu;
        ConfigJogo config = menu.executar(GG.getJanela());
        if (config.sair) {
            GG.getJanela().close();
            return;
        }

        // Reseta estados do jogo para uma nova partida limpa
        gameOver = false;
        faseTerminada = false;
        pausado = false;
        naFase2 = false;
        ninja.ressuscitar(); // Garante que o ninja começa vivo e no lugar certo

        if (config.numJogadores >= 2) {
            Controles ctrl2;
            ctrl2.esquerda = sf::Keyboard::Key::Left;
            ctrl2.direita  = sf::Keyboard::Key::Right;
            ctrl2.pular    = sf::Keyboard::Key::Up;
            ctrl2.lanca    = sf::Keyboard::Key::M;
            ninja2.emplace(350.f, 400.f, ctrl2);
        } else {
            ninja2.reset(); // Remove o jogador 2 se escolheu 1 jogador
        }

        if (config.fase == 2) {
            fase2.emplace(mapa1);
            naFase2 = true;
            if (ninja2) ninja2->setPosicao({350.f, 400.f});
        }

        // Loop de gameplay da partida atual
        // Ele vai rodar até a janela fechar OU até o jogador voltar pro menu (gameOver virar false após apertar M)
        while (GG.getJanela().isOpen()) {
            ProcessarEventos();
            
            // Se o jogador apertou M, o gameOver é resetado para false e as vidas voltam ao normal.
            // Para sair desse loop interno e recarregar o menu do while de cima, checamos se o Ninja acabou de ressuscitar:
            if (ninja.getVida() > 0 && !ninja.estaVivo()) {
                // Isso significa que saímos do Game Over pressionando M!
                break; 
            }

            Atualizar();
            Renderizar();
        }
    }
}
void Jogo::salvarJogo() {
    // 1. Abre limpando o arquivo antigo para começar um save novo do zero
    std::ofstream arquivo("assets/save_game.txt", std::ios::trunc);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de salvamento!" << std::endl;
        return;
    }
    arquivo.close(); // Fecha imediatamente, pois cada entidade abrirá em modo "append"

    // 2. Salva o Jogador 1 (e o Jogador 2 se ele existir)
    if (ninja.estaVivo()) {
        ninja.salvar();
    }
    if (ninja2 && ninja2->estaVivo()) {
        ninja2->salvar();
    }

    // 3. Ponteiro para guardar o elemento inicial da lista da fase ativa
    Listas::Lista<Entidades::Entidades>::Elemento<Entidades::Entidades>* elementoAtual = nullptr;

    if (!naFase2) {
        elementoAtual = fase1.getPrimeiroEntidade();
    } else if (fase2) {
        elementoAtual = fase2->getPrimeiroEntidade();
    }

    // 4. Percorre a lista encadeada exatamente como você fez no destrutor e no desenhar!
    while (elementoAtual != nullptr) {
        Entidades::Entidades* ent = elementoAtual->getInfo();

        if (ent) {
            // Segurança: impede de salvar o jogador novamente caso ele esteja na lista da fase
            if (ent != &ninja && (!ninja2 || ent != &*ninja2)) {
                ent->salvar(); // Chama o método polimórfico de cada Cobra, Espinho, etc.
            }
        }
        // Avança para o próximo nó da lista encadeada
        elementoAtual = elementoAtual->getProximo();
    }

    std::cout << "Jogo gravado com sucesso via Lista Encadeada!" << std::endl;
}

void Jogo::salvarRanking() {
    // ios::app garante que os novos pontos não apaguem o histórico
    std::ofstream arquivo("assets/ranking.txt", std::ios::app);
    if (arquivo.is_open()) {
        if (!nomeP1.empty()) 
            arquivo << nomeP1 << " " << ninja.getPontos() << "\n";
            
        if (ninja2 && !nomeP2.empty()) 
            arquivo << nomeP2 << " " << ninja2->getPontos() << "\n";
            
        arquivo.close();
        std::cout << "Ranking salvo com sucesso!" << std::endl;
    }
}