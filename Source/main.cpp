#include "Jogo.hpp"

#include <cstdlib>
#include <ctime>

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));   // sorteios diferentes a cada execução
    Jogo jogo;
    jogo.executar();
    return 0;
}
