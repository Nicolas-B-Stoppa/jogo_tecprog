#include "Fases/FasePrimeira.hpp"

#include "Entidades/Obstaculos/Gosma.hpp"
#include "Entidades/Personagens/Vampiro.hpp"

using namespace Entidades;

namespace Fases {

FasePrimeira::FasePrimeira(Personagens::Cacador* j1, Personagens::Cacador* j2)
    : Fase(j1, j2), maxInimMedios(5) {
    criarCenario();
}

FasePrimeira::~FasePrimeira() {}

void FasePrimeira::criarInimigos() {
    criarInimMedios();
}

void FasePrimeira::criarObstaculos() {
    criarObstMedios();
}

void FasePrimeira::criarInimMedios() {
    int quantidade = sortearQuantidade(maxInimMedios);
    for (int i = 0; i < quantidade; i++)
        incluirInimigo(new Personagens::Vampiro({sortear(700.f, LARGURA_FASE - 200.f), ALTURA_CHAO - 80.f}));
}

void FasePrimeira::criarObstMedios() {
    int quantidade = sortearQuantidade(5);
    for (int i = 0; i < quantidade; i++)
        incluirObstaculo(new Obstaculos::Gosma({sortear(400.f, LARGURA_FASE - 200.f), ALTURA_CHAO - 15.f}));
}

} // namespace Fases
