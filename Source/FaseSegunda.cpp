#include "Fases/FaseSegunda.hpp"

#include "Entidades/Personagens/Inimigos/Dracula.hpp"
#include "Entidades/Obstaculos/Estaca.hpp"

namespace Fases {

FaseSegunda::FaseSegunda() : maxChefoes(1) {
    criarInimigos();
    criarObstaculos();
}

FaseSegunda::~FaseSegunda() {}

void FaseSegunda::criarInimigos() {
    criarDraculas();
    // TODO: morcegos
}

void FaseSegunda::criarObstaculos() {
    criarPlataformas();
    criarEstacas();
}

void FaseSegunda::criarDraculas() {
    // Por enquanto um só, já em cima do chão (90 = altura do Drácula).
    Entidades::Personagens::Dracula* pDracula = new Entidades::Personagens::Dracula({2100.f, getTopoChao() - 90.f});
    incluirDracula(pDracula);
}

void FaseSegunda::criarEstacas() {
    // No chão, longe do Drácula (2100). 59 = altura da estaca.
    const float xs[] = {1400.f, 3200.f};
    for (float x : xs)
        incluirObstaculo(new Entidades::Obstaculos::Estaca({x, getTopoChao() - 59.f}));
}

} // namespace Fases
