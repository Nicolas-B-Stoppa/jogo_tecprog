#include "Fases/FaseSegunda.hpp"

#include "Entidades/Personagens/Inimigos/Dracula.hpp"
#include "Entidades/Obstaculos/Estaca.hpp"

#include <cstdlib>

namespace Fases {

FaseSegunda::FaseSegunda() : maxChefoes(1) {
    criarInimigos();
    criarObstaculos();
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

void FaseSegunda::criarDraculas() {
    // Mesmos lugares dos vampiros da fase 1. 3 sempre aparecem e 2 têm 50% de chance.
    // 90 = altura do Drácula.
    Entidades::Personagens::Dracula* pDracula1 = new Entidades::Personagens::Dracula({1450.f, getTopoChao() - 90.f});
    incluirDracula(pDracula1);
    Entidades::Personagens::Dracula* pDracula2 = new Entidades::Personagens::Dracula({2250.f, getTopoChao() - 90.f});
    incluirDracula(pDracula2);
    Entidades::Personagens::Dracula* pDracula3 = new Entidades::Personagens::Dracula({3050.f, getTopoChao() - 90.f});
    incluirDracula(pDracula3);
    if (rand() % 2) {
        Entidades::Personagens::Dracula* pDracula4 = new Entidades::Personagens::Dracula({3850.f, getTopoChao() - 90.f});
        incluirDracula(pDracula4);
    }
    if (rand() % 2) {
        Entidades::Personagens::Dracula* pDracula5 = new Entidades::Personagens::Dracula({4650.f, getTopoChao() - 90.f});
        incluirDracula(pDracula5);
    }
}

void FaseSegunda::criarEstacas() {
    // No chão, longe do Drácula (2100). 59 = altura da estaca.
    const float xs[] = {1400.f, 3200.f};
    for (float x : xs)
        incluirObstaculo(new Entidades::Obstaculos::Estaca({x, getTopoChao() - 59.f}));
}

} // namespace Fases
