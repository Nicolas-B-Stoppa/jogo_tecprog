#include "Fases/FasePrimeira.hpp"

#include "Entidades/Personagens/Inimigos/Vampiro.hpp"
#include "Entidades/Obstaculos/Gosma.hpp"

#include <cstdlib>
#include <fstream>

namespace Fases {

FasePrimeira::FasePrimeira(bool carregando) : maxINIMMedios(3) {
    if (carregando) {
        carregarInimigos();
        carregarObstaculos();
    } else {
        criarInimigos();
        criarObstaculos();
    }
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

void FasePrimeira::carregarInimigos() {
    carregarMorcegos();
    carregarVampiros();
}

void FasePrimeira::carregarObstaculos() {
    carregarPlataformas();
    carregarGosmas();
}

void FasePrimeira::carregarVampiros() {
    std::ifstream arquivo("save/vampiros.txt");
    float x, y;
    while (arquivo >> x >> y) {
        Entidades::Personagens::Vampiro* pVampiro = new Entidades::Personagens::Vampiro({x, y});
        pVampiro->carregar(arquivo);
        incluirInimigo(pVampiro);
    }
}

void FasePrimeira::carregarGosmas() {
    std::ifstream arquivo("save/gosmas.txt");
    float x, y;
    while (arquivo >> x >> y) {
        Entidades::Obstaculos::Gosma* pGosma = new Entidades::Obstaculos::Gosma({x, y});
        pGosma->carregar(arquivo);
        incluirObstaculo(pGosma);
    }
}

void FasePrimeira::criarVampiros() {
    // 3 sempre aparecem e 2 têm 1 chance em 3. 70 = altura do vampiro.
    Entidades::Personagens::Vampiro* pVampiro1 = new Entidades::Personagens::Vampiro({1450.f, getTopoChao() - 70.f});
    incluirInimigo(pVampiro1);
    Entidades::Personagens::Vampiro* pVampiro2 = new Entidades::Personagens::Vampiro({2250.f, getTopoChao() - 70.f});
    incluirInimigo(pVampiro2);
    Entidades::Personagens::Vampiro* pVampiro3 = new Entidades::Personagens::Vampiro({3050.f, getTopoChao() - 70.f});
    incluirInimigo(pVampiro3);
    if (!(rand() % 3)) {
        Entidades::Personagens::Vampiro* pVampiro4 = new Entidades::Personagens::Vampiro({3850.f, getTopoChao() - 70.f});
        incluirInimigo(pVampiro4);
    }
    if (!(rand() % 3)) {
        Entidades::Personagens::Vampiro* pVampiro5 = new Entidades::Personagens::Vampiro({4650.f, getTopoChao() - 70.f});
        incluirInimigo(pVampiro5);
    }
}

void FasePrimeira::criarGosmas() {
    // No chão, fora de baixo das plataformas. 3 sempre aparecem e 1 tem 50% de chance.
    float y = getTopoChao() - Entidades::Obstaculos::Gosma::TAMANHO.y;   // em cima do chão
    Entidades::Obstaculos::Gosma* pGosma1 = new Entidades::Obstaculos::Gosma({500.f, y});
    incluirObstaculo(pGosma1);
    Entidades::Obstaculos::Gosma* pGosma2 = new Entidades::Obstaculos::Gosma({1800.f, y});
    incluirObstaculo(pGosma2);
    Entidades::Obstaculos::Gosma* pGosma3 = new Entidades::Obstaculos::Gosma({3100.f, y});
    incluirObstaculo(pGosma3);
    if (rand() % 2) {
        Entidades::Obstaculos::Gosma* pGosma4 = new Entidades::Obstaculos::Gosma({4300.f, y});
        incluirObstaculo(pGosma4);
    }
}

} // namespace Fases
