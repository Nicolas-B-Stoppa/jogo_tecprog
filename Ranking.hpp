#pragma once

#include <string>
#include <vector>

// Os 10 maiores pontos, do maior para o menor, guardados em ranking.txt
// (uma linha por registro: "pontos nome").
class Ranking {
private:
    std::vector<std::string> nomes;
    std::vector<int> pontos;

    void salvar();

public:
    Ranking();
    ~Ranking();

    void carregar();
    void incluir(const std::string& nome, int pts);   // já salva no arquivo

    int getQuantidade() const;
    std::string getNome(int i) const;
    int getPontos(int i) const;
};
