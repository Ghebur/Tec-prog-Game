#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

struct Pontuacao {
    std::string nome;
    int pontos;
    
    bool operator<(const Pontuacao& outra) const {
        return pontos > outra.pontos; 
    }
};

class GerenciadorRanking {
private:
    std::string caminhoArquivo;

public:
    GerenciadorRanking();
    ~GerenciadorRanking();

    void salvarPontuacao(const std::string& nome, int pontos);
    std::vector<Pontuacao> carregarRanking();
};