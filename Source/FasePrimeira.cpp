#include "Fases/FasePrimeira.hpp"

#include "Entidades/Personagens/Inimigos/Morcego.hpp"
#include "Entidades/Personagens/Inimigos/Vampiro.hpp"
#include "Entidades/Obstaculos/Gosma.hpp"

namespace Fases {

FasePrimeira::FasePrimeira() : maxINIMMedios(3) {
    
    criarInimigos();
    criarObstaculos();
}

FasePrimeira::~FasePrimeira() {}

void FasePrimeira::criarInimigos() {
    criarMorcegos();
    criarVampiros();
}

void FasePrimeira::criarObstaculos() {
    criarPlataformas();
    criarGosmas();
}

void FasePrimeira::criarMorcegos() {
    // Por enquanto um só, voando no começo da fase.
    Entidades::Personagens::Morcego* pMorcego = new Entidades::Personagens::Morcego({1200.f, 520.f});
    incluirInimigo(pMorcego);
}

void FasePrimeira::criarVampiros() {
    // Por enquanto um só, longe do morcego.
    Entidades::Personagens::Vampiro* pVampiro = new Entidades::Personagens::Vampiro({1700.f, getTopoChao() - 70.f});
    incluirInimigo(pVampiro);
}

void FasePrimeira::criarGosmas() {
    // No chão, longe do morcego (1200) e do vampiro (1700).
    const float xs[] = {600.f, 2300.f};
    for (float x : xs)
        incluirObstaculo(new Entidades::Obstaculos::Gosma({x, getTopoChao() - Entidades::Obstaculos::Gosma::TAMANHO.y}));
}

} // namespace Fases
