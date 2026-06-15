#include "../gerenciadores/Gerenciador_Ranking.h"

GerenciadorRanking::GerenciadorRanking() : caminhoArquivo("assets/ranking.txt") {}
GerenciadorRanking::~GerenciadorRanking() {}

void GerenciadorRanking::salvarPontuacao(const std::string& nome, int pontos) {
        std::ofstream arquivo(caminhoArquivo, std::ios::app);
        if (arquivo.is_open()) {
            arquivo << nome << " " << pontos << "\n";
            arquivo.close();
        }
    }

    std::vector<Pontuacao> GerenciadorRanking::carregarRanking() {
        std::vector<Pontuacao> lista;
        std::ifstream arquivo(caminhoArquivo);
        if (!arquivo.is_open()) return lista;

        std::string nome;
        int pontos;
        while (arquivo >> nome >> pontos) {
            lista.push_back({nome, pontos});
        }
        arquivo.close();

        std::sort(lista.begin(), lista.end());
        return lista;
    }