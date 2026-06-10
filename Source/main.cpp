#include <SFML/Graphics.hpp>
#include <optional>
#include <cstdlib>
#include <ctime>
#include "../Jogo.h"

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    Jogo meuJogo;
    meuJogo.Rodar(); 
    
    return 0;
}