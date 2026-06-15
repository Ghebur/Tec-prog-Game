#include <cmath>
#include "../Jogo.h"
#include <fstream>
#include <iostream> 

Jogo::Jogo() :
    GG(sf::VideoMode({800, 600}), "Meu Jogo UTFPR"),
    ninja(300.f, 400.f),
    mapa1(),
    fase1(mapa1),
    textoPausa(fonteHUD),
    textoVidas(fonteHUD),
    textoTempo(fonteHUD),
    textoVidas2(fonteHUD),
    textoTempo2(fonteHUD)
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
        textoVidas.setFillColor(sf::Color::White);
        textoVidas.setPosition({20.f, 20.f});

        textoTempo.setFont(fonteHUD);
        textoTempo.setCharacterSize(22);
        textoTempo.setFillColor(sf::Color::White);
        textoTempo.setPosition({20.f, 50.f});

        textoVidas2.setFont(fonteHUD);
        textoVidas2.setCharacterSize(22);
        textoVidas2.setFillColor(sf::Color::White);
        textoVidas2.setPosition({525.f, 20.f});

        textoTempo2.setFont(fonteHUD);
        textoTempo2.setCharacterSize(22);
        textoTempo2.setFillColor(sf::Color::White);
        textoTempo2.setPosition({525.f, 50.f});
    }
}

Jogo::~Jogo() {}

void Jogo::Atualizar() {
    if (faseTerminada) return;

    sf::Vector2f posCamera = ninja.getPos();
    posCamera.y = 300.f;
    camera.setCenter(posCamera);

    if (pausado) return; 

    if (!naFase2) {
        fase1.atualizarInimigos(mapa1, ninja);
        if (ninja.estaVivo()) ninja.update(mapa1);
        ninja.setEmOleo(false);
        fase1.processarObstaculos(ninja);
        fase1.verificarTransicaoFase(ninja);

        if (ninja2) {
            if (ninja2->estaVivo()) ninja2->update(mapa1);
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
        if (ninja.estaVivo()) ninja.update(mapa1);
        ninja.setEmOleo(false);
        fase2->processarObstaculos(ninja);
        fase2->verificarTransicaoFase(ninja);

        if (ninja2) {
            if (ninja2->estaVivo()) ninja2->update(mapa1);
            ninja2->setEmOleo(false);
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

    // ADICIONADO: Menu visual de Pausa (Desenha por cima do cenário/entidades, mas sob a HUD fixada)
    if (pausado) {
        sf::RectangleShape overlay({800.f, 600.f});
        overlay.setPosition(camera.getCenter() - sf::Vector2f(400.f, 300.f));
        overlay.setFillColor(sf::Color(0, 0, 0, 160)); // Filtro preto semi-transparente
        window.draw(overlay);

        textoPausa.setFont(fonteHUD);
        textoPausa.setString("JOGO PAUSADO\n\n[P] Retornar ao Jogo\n[S] Salvar Jogada");
        textoPausa.setCharacterSize(32);
        textoPausa.setFillColor(sf::Color::White);
        
        // Centralização perfeita do texto em relação ao meio da câmera ativa
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

    // Retorna para a visualização padrão fixada na janela para renderizar a HUD estática
    window.setView(window.getDefaultView());
    
    textoVidas.setString("Vidas: " + std::to_string(ninja.getVida()));
    float tempoArmar = ninja.getTempoParaArmar();
    std::string tempoArmarTexto = tempoArmar > 0.f
        ? std::to_string(static_cast<int>(std::ceil(tempoArmar))) + "s"
        : "Pronto";
    textoTempo.setString("Tempo p/ armar: " + tempoArmarTexto);
    window.draw(textoVidas);
    window.draw(textoTempo);

    if (ninja2) {
        textoVidas2.setString("P2 Vidas: " + std::to_string(ninja2->getVida()));
        float tempoArmar2 = ninja2->getTempoParaArmar();
        std::string tempoArmar2Texto = tempoArmar2 > 0.f
            ? std::to_string(static_cast<int>(std::ceil(tempoArmar2))) + "s"
            : "Pronto";
        textoTempo2.setString("P2 Tempo p/ armar: " + tempoArmar2Texto);
        window.draw(textoVidas2);
        window.draw(textoTempo2);
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
        }
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
    Lista<Entidades>::Elemento<Entidades>* elementoAtual = nullptr;

    if (!naFase2) {
        elementoAtual = fase1.getPrimeiroEntidade();
    } else if (fase2) {
        elementoAtual = fase2->getPrimeiroEntidade();
    }

    // 4. Percorre a lista encadeada exatamente como você fez no destrutor e no desenhar!
    while (elementoAtual != nullptr) {
        Entidades* ent = elementoAtual->getInfo();

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