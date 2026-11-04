#include "Fases/Fase.hpp"

#include <cstdlib>

#include "Entidades/Obstaculos/Plataforma.hpp"
#include "Entidades/Personagens/Cacador.hpp"
#include "Entidades/Personagens/Morcego.hpp"

using namespace Entidades;

namespace Fases {

Fase::Fase(Personagens::Cacador* j1, Personagens::Cacador* j2)
    : lista_ents(), GC(), pJog1(j1), pJog2(j2) {
    GC.setJogadores(pJog1, pJog2);
}

Fase::~Fase() {
    GC.limpar();
    lista_ents.limpar();
}

void Fase::incluirInimigo(Personagens::Inimigo* pi) {
    pi->setJogador(pJog1);
    lista_ents.incluir(pi);
    GC.incluirInimigo(pi);
}

void Fase::incluirObstaculo(Obstaculos::Obstaculo* po) {
    lista_ents.incluir(po);
    GC.incluirObstaculo(po);
}

float Fase::sortear(float min, float max) const {
    return min + (max - min) * (std::rand() / static_cast<float>(RAND_MAX));
}

int Fase::sortearQuantidade(int max) const {
    const int minimo = 3;
    if (max <= minimo)
        return minimo;
    return minimo + std::rand() % (max - minimo + 1);
}

void Fase::criarInimFaceis() {
    int quantidade = sortearQuantidade(5);
    for (int i = 0; i < quantidade; i++)
        incluirInimigo(new Personagens::Morcego({sortear(500.f, LARGURA_FASE - 300.f), sortear(300.f, 450.f)}));
}

void Fase::criarPlataformas() {
    // Chão: uma fileira de plataformas.
    for (float x = 0.f; x < LARGURA_FASE; x += 200.f)
        incluirObstaculo(new Obstaculos::Plataforma({x, ALTURA_CHAO}, {200.f, 70.f}));

    // Plataformas suspensas.
    int quantidade = sortearQuantidade(6);
    for (int i = 0; i < quantidade; i++)
        incluirObstaculo(new Obstaculos::Plataforma(
            {(i + 1) * LARGURA_FASE / (quantidade + 1), sortear(420.f, 520.f)}, {150.f, 25.f}));
}

void Fase::criarCenario() {
    criarPlataformas();
    criarInimFaceis();
    criarInimigos();
    criarObstaculos();
}

void Fase::executar() {
    lista_ents.percorrer();

    if (pJog1 && pJog1->estaVivo()) { pJog1->executar(); pJog1->desenhar(); }
    if (pJog2 && pJog2->estaVivo()) { pJog2->executar(); pJog2->desenhar(); }

    GC.executar();
}

void Fase::criarProjetil(sf::Vector2f, float) {
    // Por padrão a fase não tem projéteis (ver FaseSegunda).
}

bool Fase::concluida() const {
    return GC.todosInimigosMortos();
}

bool Fase::jogadoresMortos() const {
    bool vivo1 = pJog1 && pJog1->estaVivo();
    bool vivo2 = pJog2 && pJog2->estaVivo();
    return !vivo1 && !vivo2;
}

} // namespace Fases
