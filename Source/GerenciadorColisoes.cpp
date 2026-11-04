#include "Gerenciadores/GerenciadorColisoes.hpp"

#include "Entidades/Obstaculos/Obstaculo.hpp"
#include "Entidades/Personagens/Cacador.hpp"
#include "Entidades/Personagens/Inimigo.hpp"
#include "Entidades/Sangue.hpp"

using Entidades::Entidade;
using Entidades::Sangue;
using Entidades::Obstaculos::Obstaculo;
using Entidades::Personagens::Cacador;
using Entidades::Personagens::Inimigo;

namespace Gerenciadores {

GerenciadorColisoes::GerenciadorColisoes() : pJog1(nullptr), pJog2(nullptr) {}

GerenciadorColisoes::~GerenciadorColisoes() {
    limpar();
}

bool GerenciadorColisoes::verificarColisao(const Entidade* pe1, const Entidade* pe2) const {
    if (!pe1 || !pe2 || !pe1->getAtivo() || !pe2->getAtivo())
        return false;
    return pe1->getLimites().findIntersection(pe2->getLimites()).has_value();
}

void GerenciadorColisoes::incluirInimigo(Inimigo* pi) { if (pi) LIs.push_back(pi); }
void GerenciadorColisoes::incluirObstaculo(Obstaculo* po) { if (po) LOs.push_back(po); }
void GerenciadorColisoes::incluirProjetil(Sangue* pj) { if (pj) LPs.insert(pj); }

void GerenciadorColisoes::setJogadores(Cacador* j1, Cacador* j2) {
    pJog1 = j1;
    pJog2 = j2;
}

bool GerenciadorColisoes::todosInimigosMortos() const {
    for (Inimigo* pi : LIs)
        if (pi->estaVivo())
            return false;
    return true;
}

// --- Jogadores x Obstáculos ---
void GerenciadorColisoes::tratarColisoesJogObstacs(Cacador* pJog) {
    if (!pJog || !pJog->estaVivo())
        return;
    for (Obstaculo* po : LOs)
        if (verificarColisao(pJog, po))
            po->obstaculizar(pJog);
}

void GerenciadorColisoes::tratarColisoesJogsObstacs() {
    tratarColisoesJogObstacs(pJog1);
    tratarColisoesJogObstacs(pJog2);
}

// --- Jogadores x Inimigos ---
void GerenciadorColisoes::tratarColisoesJogInimgs(Cacador* pJog) {
    if (!pJog || !pJog->estaVivo())
        return;
    for (Inimigo* pi : LIs)
        if (pi->estaVivo())
            pJog->colidir(pi);   // o Cacador decide se ataca ou é atacado
}

void GerenciadorColisoes::tratarColisoesJogsInimgs() {
    tratarColisoesJogInimgs(pJog1);
    tratarColisoesJogInimgs(pJog2);
}

// --- Jogadores x Projéteis ---
void GerenciadorColisoes::tratarColisoesJogProjeteis(Cacador* pJog) {
    if (!pJog || !pJog->estaVivo())
        return;
    for (Sangue* pj : LPs)
        if (verificarColisao(pJog, pj))
            pj->danificar(pJog);
}

void GerenciadorColisoes::tratarColisoesJogsProjeteis() {
    tratarColisoesJogProjeteis(pJog1);
    tratarColisoesJogProjeteis(pJog2);

    // Projétil que encosta em obstáculo some.
    for (Sangue* pj : LPs)
        for (Obstaculo* po : LOs)
            if (verificarColisao(pj, po))
                pj->setAtivo(false);
}

// --- Inimigos x Obstáculos ---
void GerenciadorColisoes::tratarColisoesInimgsObstacs() {
    for (Inimigo* pi : LIs) {
        if (!pi->estaVivo())
            continue;
        for (Obstaculo* po : LOs)
            if (verificarColisao(pi, po))
                po->obstaculizar(pi);
    }
}

void GerenciadorColisoes::executar() {
    tratarColisoesInimgsObstacs();
    tratarColisoesJogsObstacs();
    tratarColisoesJogsInimgs();
    tratarColisoesJogsProjeteis();
}

void GerenciadorColisoes::limpar() {
    // Só esquece os ponteiros: quem deleta é a ListaEntidades da Fase.
    LIs.clear();
    LOs.clear();
    LPs.clear();
}

} // namespace Gerenciadores
