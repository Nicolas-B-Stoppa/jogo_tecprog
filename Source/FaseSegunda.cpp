#include "Fases/FaseSegunda.hpp"

#include "Entidades/Personagens/Inimigos/Dracula.hpp"
#include "Entidades/Obstaculos/Estaca.hpp"

#include <cstdlib>
#include <fstream>

namespace Fases {

FaseSegunda::FaseSegunda(bool carregando)
    : maxChefoes(3 + rand() % 3),
      maxEstacas(3 + rand() % 3) {
    if (carregando) {
        carregarInimigos();
        carregarObstaculos();
    } else {
        criarInimigos();
        criarObstaculos();
    }
}

FaseSegunda::~FaseSegunda() {}

void FaseSegunda::criarInimigos() {
    criarDraculas();
    criarMorcegos();
}

void FaseSegunda::criarObstaculos() {
    criarPlataformas();
    criarEstacas();
}

void FaseSegunda::carregarInimigos() {
    carregarDraculas();
    carregarMorcegos();
}

void FaseSegunda::carregarObstaculos() {
    carregarPlataformas();
    carregarEstacas();
}

void FaseSegunda::carregarDraculas() {
    // Cada Drácula ocupa duas linhas: a dele e a do sangue (o carregar dele lê as duas).
    std::ifstream arquivo("save/draculas.txt");
    float x, y;
    while (arquivo >> x >> y) {
        Entidades::Personagens::Dracula* pDracula = new Entidades::Personagens::Dracula({x, y});
        pDracula->carregar(arquivo);
        incluirDracula(pDracula);
    }
}

void FaseSegunda::carregarEstacas() {
    std::ifstream arquivo("save/estacas.txt");
    float x, y;
    while (arquivo >> x >> y) {
        Entidades::Obstaculos::Estaca* pEstaca = new Entidades::Obstaculos::Estaca({x, y});
        pEstaca->carregar(arquivo);
        incluirObstaculo(pEstaca);
    }
}

void FaseSegunda::criarDraculas() {
    // Mesmos lugares dos vampiros da fase 1. 3 sempre aparecem; o 4º e o 5º dependem do maxChefoes.
    // 90 = altura do Drácula.
    // O 1 nasce em cima da plataforma 1 (900 a 1100, 140 acima do chão); andando, ele cai.
    Entidades::Personagens::Dracula* pDracula1 = new Entidades::Personagens::Dracula({980.f, getTopoChao() - 140.f - 90.f});
    incluirDracula(pDracula1);
    Entidades::Personagens::Dracula* pDracula2 = new Entidades::Personagens::Dracula({2250.f, getTopoChao() - 90.f});
    incluirDracula(pDracula2);
    Entidades::Personagens::Dracula* pDracula3 = new Entidades::Personagens::Dracula({3050.f, getTopoChao() - 90.f});
    incluirDracula(pDracula3);
    if (maxChefoes >= 4) {
        Entidades::Personagens::Dracula* pDracula4 = new Entidades::Personagens::Dracula({3850.f, getTopoChao() - 90.f});
        incluirDracula(pDracula4);
    }
    if (maxChefoes >= 5) {
        Entidades::Personagens::Dracula* pDracula5 = new Entidades::Personagens::Dracula({4650.f, getTopoChao() - 90.f});
        incluirDracula(pDracula5);
    }
}

void FaseSegunda::criarEstacas() {
    // No chão. 3 sempre aparecem; a 4ª e a 5ª dependem do maxEstacas. 59 = altura da estaca.
    Entidades::Obstaculos::Estaca* pEstaca1 = new Entidades::Obstaculos::Estaca({600.f, getTopoChao() - 59.f});
    incluirObstaculo(pEstaca1);
    Entidades::Obstaculos::Estaca* pEstaca2 = new Entidades::Obstaculos::Estaca({1400.f, getTopoChao() - 59.f});
    incluirObstaculo(pEstaca2);
    Entidades::Obstaculos::Estaca* pEstaca3 = new Entidades::Obstaculos::Estaca({3200.f, getTopoChao() - 59.f});
    incluirObstaculo(pEstaca3);
    if (maxEstacas >= 4) {
        Entidades::Obstaculos::Estaca* pEstaca4 = new Entidades::Obstaculos::Estaca({2000.f, getTopoChao() - 59.f});
        incluirObstaculo(pEstaca4);
    }
    if (maxEstacas >= 5) {
        Entidades::Obstaculos::Estaca* pEstaca5 = new Entidades::Obstaculos::Estaca({4300.f, getTopoChao() - 59.f});
        incluirObstaculo(pEstaca5);
    }
}

} // namespace Fases
