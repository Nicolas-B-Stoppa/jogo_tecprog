#include "Fases/FaseSegunda.hpp"

#include "Entidades/Obstaculos/Estaca.hpp"
#include "Entidades/Personagens/Dracula.hpp"
#include "Entidades/Sangue.hpp"

using namespace Entidades;

namespace Fases {

FaseSegunda::FaseSegunda(Personagens::Cacador* j1, Personagens::Cacador* j2)
    : Fase(j1, j2), maxChefes(1) {
    criarCenario();
}

FaseSegunda::~FaseSegunda() {}

void FaseSegunda::criarInimigos() {
    criarChefes();
}

void FaseSegunda::criarObstaculos() {
    criarObstDificeis();
}

void FaseSegunda::criarChefes() {
    for (int i = 0; i < maxChefes; i++)
        incluirInimigo(new Personagens::Dracula({LARGURA_FASE - 400.f - i * 300.f, ALTURA_CHAO - 110.f}, this));
}

void FaseSegunda::criarObstDificeis() {
    int quantidade = sortearQuantidade(6);
    for (int i = 0; i < quantidade; i++)
        incluirObstaculo(new Obstaculos::Estaca({sortear(400.f, LARGURA_FASE - 600.f), ALTURA_CHAO - 30.f}));
}

void FaseSegunda::criarProjetil(sf::Vector2f posicao, float direcao) {
    Sangue* pS = new Sangue(posicao, direcao);
    lista_ents.incluir(pS);
    GC.incluirProjetil(pS);
}

} // namespace Fases
