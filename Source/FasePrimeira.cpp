#include "Fases/FasePrimeira.hpp"

#include "Entidades/Personagens/Inimigos/Morcego.hpp"
#include "Entidades/Personagens/Inimigos/Vampiro.hpp"

namespace Fases {

FasePrimeira::FasePrimeira() {
    
    criarInimigos();
    criarObstaculos();
}

FasePrimeira::~FasePrimeira() {}

void FasePrimeira::criarInimigos() {
    criarMorcegos();
    criarVampiros();
}

void FasePrimeira::criarObstaculos() {
    // TODO: gosmas e plataformas
}

void FasePrimeira::criarMorcegos() {
    // Por enquanto um só, voando no começo da fase.
    Entidades::Personagens::Morcego* pMorcego = new Entidades::Personagens::Morcego({1200.f, 520.f});
    pMorcego->setChao(getTopoChao());
    incluirInimigo(pMorcego);
}

void FasePrimeira::criarVampiros() {
    // Por enquanto um só, longe do morcego.
    Entidades::Personagens::Vampiro* pVampiro = new Entidades::Personagens::Vampiro({1700.f, getTopoChao() - 70.f});
    pVampiro->setChao(getTopoChao());
    incluirInimigo(pVampiro);
}

} // namespace Fases
