#include "Ranking.hpp"

#include <fstream>

Ranking::Ranking() {}

Ranking::~Ranking() {}

void Ranking::carregar() {
    nomes.clear();
    pontos.clear();

    std::ifstream arquivo("ranking.txt");
    int pts;
    std::string nome;
    // Cada linha: pontos e depois o nome (sem espaços).
    while (arquivo >> pts >> nome) {
        nomes.push_back(nome);
        pontos.push_back(pts);
    }
}

void Ranking::incluir(const std::string& nome, int pts) {
    // Procura a primeira posição com menos pontos: o novo entra antes dela.
    int pos = 0;
    while (pos < getQuantidade() && pontos[pos] >= pts)
        pos++;

    nomes.insert(nomes.begin() + pos, nome);
    pontos.insert(pontos.begin() + pos, pts);

    // Só os 10 maiores ficam.
    if (getQuantidade() > 10) {
        nomes.pop_back();
        pontos.pop_back();
    }

    salvar();
}

void Ranking::salvar() {
    std::ofstream arquivo("ranking.txt");
    for (int i = 0; i < getQuantidade(); i++)
        arquivo << pontos[i] << " " << nomes[i] << "\n";
}

int Ranking::getQuantidade() const {
    return static_cast<int>(nomes.size());
}

std::string Ranking::getNome(int i) const {
    return nomes[i];
}

int Ranking::getPontos(int i) const {
    return pontos[i];
}
