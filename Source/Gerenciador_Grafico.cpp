#include "../gerenciadores/Gerenciador_Grafico.h"

namespace Gerenciadores {

Gerenciador_Grafico::Gerenciador_Grafico(sf::VideoMode modo, const std::string& titulo)
    : janela(modo, titulo)
{}

Gerenciador_Grafico::~Gerenciador_Grafico() {}

void Gerenciador_Grafico::desenharEnte(Ent* pE) {
    pE->desenhar(janela);
}

sf::RenderWindow& Gerenciador_Grafico::getJanela() {
    return janela;
}

} // namespace Gerenciadores
