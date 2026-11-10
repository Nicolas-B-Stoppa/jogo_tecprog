#include "Fases/FaseSegunda.hpp"

#include "Entidades/Personagens/Inimigos/Dracula.hpp"

namespace Fases {

FaseSegunda::FaseSegunda() {
    criarInimigos();
    criarObstaculos();
}

FaseSegunda::~FaseSegunda() {}

void FaseSegunda::criarInimigos() {
    criarDraculas();
    // TODO: morcegos
}

void FaseSegunda::criarObstaculos() {
    // TODO: estacas e plataformas
}

void FaseSegunda::criarDraculas() {
    // Por enquanto um só, já em cima do chão (90 = altura do Drácula).
    Entidades::Personagens::Dracula* pDracula = new Entidades::Personagens::Dracula({2100.f, getTopoChao() - 90.f});
    incluirDracula(pDracula);
}

} // namespace Fases
