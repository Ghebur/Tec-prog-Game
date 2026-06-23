#include "../Entidades/Personagens/Samurai.h"
#include "../Figura.h"
#include <fstream>

namespace Personagens {                                                                             

Samurai::Samurai(float x, float y) :
Inimigo(3, 2, {3.f, 0.f}, 50.f, {x, y}, 1),
corpo(sf::Vector2f(12.f, 12.f)),
graduacao(rand()%3+1)
{
    vida = graduacao;
    corpo.setPosition(posicao);
    texRun.loadFromFile("assets/SamuraiAnimacoes/Run.png");

    pFig = new Figura(texRun);
    pFig->getSprite().setTextureRect(sf::IntRect{{0, 0}, {FRAME_W, FRAME_H}});
    float escala = tamanho / FRAME_H;
    pFig->getSprite().setScale({escala, escala});
    pFig->getSprite().setPosition(posicao);
}

Samurai::~Samurai() {}

sf::FloatRect Samurai::getBounds() {
    return {posicao, corpo.getSize()};
}


void Samurai::danifcar(Personagens& p) {
    for(int i =0;i<=nivelDeMaldade;i++)
        --p;
    
}

void Samurai::pular() {
    float sinAtual = std::sin(angulo);
    if (ultimoSin < 0.f && sinAtual >= 0.f && noChao) {
        velocidade.y = -167.f;
        noChao = false;
    }
    ultimoSin = sinAtual;
}

void Samurai::executar(Mapa1& mapa, Personagens& p) {
    movimentacao();
    pular();
    aplicarGravidade(1.f / 60.f);
    verificarColisaoChao(mapa, corpo.getSize().y);

}

void Samurai::atualizarAnimacao(){
    float escala = (tamanho / FRAME_H);
    int totalFrames = 8;
    sf::Vector2f pos = posicao;

    pos.y = posicao.y - 38.f;

    if (relogioAnim.getElapsedTime().asSeconds() > 0.1f) {
        frameAtual = (frameAtual + 1) % totalFrames;
        relogioAnim.restart();
    }
    //verifica se a deraivada de sen (cos) é negativa pra se basear no lado que o sprite está 
    bool indoPDireita = std::cos(angulo) > 0;
    
    pFig->getSprite().setTextureRect(sf::IntRect{{frameAtual * FRAME_W, 0}, {FRAME_W, FRAME_H}});

    if(!indoPDireita){
        pFig->getSprite().setScale({-escala, escala});
        pFig->getSprite().setOrigin({static_cast<float>(FRAME_W), 0.f});
    }
    else{
        pFig->getSprite().setScale({escala, escala});
        pFig->getSprite().setOrigin({0.f, 0.f});
    }

    pFig->getSprite().setPosition(pos);
}

void Samurai::salvar() {
    SalvarDataBuffer();
    buffer += std::to_string(id) + " " + std::to_string(graduacao) + " " +  std::to_string(origemX) + " " +  std::to_string(angulo) + "\n";
    std::ofstream arquivo("assets/save_samurai.txt", std::ios::app);
    if (arquivo.is_open()) {
        arquivo << buffer;
        arquivo.close();
    }
}

} // namespace Personagens
