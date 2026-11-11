#include "Gerenciadores/GerenciadorColisoes.hpp"

#include "Entidades/Entidade.hpp"
#include "Entidades/Personagens/Cacador.hpp"
#include "Entidades/Personagens/Inimigos/Inimigo.hpp"
#include "Entidades/Personagens/Inimigos/Dracula.hpp"
#include "Entidades/Sangue.hpp"
#include "Entidades/Obstaculos/Obstaculo.hpp"

namespace Gerenciadores {

GerenciadorColisoes::GerenciadorColisoes() : pJog1(nullptr), pJog2(nullptr), topoChao(720.f) {}

GerenciadorColisoes::~GerenciadorColisoes() {
    // Só esvazia as listas; quem deleta as entidades é a ListaEntidades da fase.
    LIs.clear();
    LOs.clear();
    LPs.clear();
    pJog1 = nullptr;
    pJog2 = nullptr;
}

void GerenciadorColisoes::incluirInimigo(Entidades::Personagens::Inimigo* pi) {
    if (pi)
        LIs.push_back(pi);
}

void GerenciadorColisoes::incluirObstaculo(Entidades::Obstaculos::Obstaculo* po) {
    if (po)
        LOs.push_back(po);
}

void GerenciadorColisoes::incluirProjetil(Entidades::Sangue* pj) {
    if (pj)
        LPs.insert(pj);   
}

void GerenciadorColisoes::setJogadores(Entidades::Personagens::Cacador* pj1,
                                       Entidades::Personagens::Cacador* pj2) {
    pJog1 = pj1;
    pJog2 = pj2;
}

void GerenciadorColisoes::setTopoChao(float y) {
    topoChao = y;
}

bool GerenciadorColisoes::verificaColisao(Entidades::Entidade* pEnt1, Entidades::Entidade* pEnt2) const{

    if (!pEnt1 || !pEnt2)
        return false;

    sf::FloatRect r1(pEnt1->getPosicao(), pEnt1->getTamanho());
    sf::FloatRect r2(pEnt2->getPosicao(), pEnt2->getTamanho());
    return r1.findIntersection(r2).has_value();


}

void GerenciadorColisoes::executar() {
    colisaoChao();   // primeiro todo mundo para em cima do chão
    colisaoInimigoJog();
    colisaoProjetilJog();
    // TODO: descomentar quando estiver implementado
    // colisaoObstaculoJog();
}

void GerenciadorColisoes::colisaoChao(Entidades::Entidade* pEnt) {
    if (!pEnt)
        return;

    // Encostou no chão: o gerenciador coloca a entidade em cima dele.
    if (pEnt->getPosicao().y + pEnt->getTamanho().y >= topoChao)
        pEnt->pousar(topoChao);
}

void GerenciadorColisoes::colisaoChao() {
    for (Entidades::Personagens::Inimigo* pIni : LIs)
        colisaoChao(pIni);
    colisaoChao(pJog1);
    colisaoChao(pJog2);

    // O sangue não pousa: encostou no chão, some.
    for (Entidades::Sangue* pSangue : LPs) {
        if (pSangue->estaAtiva() && pSangue->getPosicao().y + pSangue->getTamanho().y >= topoChao)
            pSangue->desativar();
    }
}

void GerenciadorColisoes::colisaoInimigoJog() {
    for (Entidades::Personagens::Inimigo* pIni : LIs) {
        colisaoInimigoJog(pIni, pJog1);
        colisaoInimigoJog(pIni, pJog2);
    }
}

void GerenciadorColisoes::colisaoInimigoJog(Entidades::Personagens::Inimigo* pIni,
                                            Entidades::Personagens::Cacador* pJog) {
    if (!pJog || !verificaColisao(pIni, pJog))
        return;

    if (pJog->estaArmado()) {
        // Encostou no caçador armado: quem leva o dano é o inimigo
        // (se não acabou de levar outro golpe).
        if (!pIni->estaInvencivel())
            pJog->atacar(pIni);
    } else if (!pJog->estaInvencivel()) {
        pIni->danificar(pJog);     // o danificar já aplica o knockback
    }
}

void GerenciadorColisoes::colisaoProjetilJog() {
    for (Entidades::Sangue* pSangue : LPs) {
        colisaoProjetilJog(pSangue, pJog1);
        colisaoProjetilJog(pSangue, pJog2);
    }
}

void GerenciadorColisoes::colisaoProjetilJog(Entidades::Sangue* pSangue, Entidades::Personagens::Cacador* pJog) {
    if (!pJog || !pSangue->estaAtiva() || !verificaColisao(pSangue, pJog))
        return;

    if (!pJog->estaInvencivel())
        pSangue->danificar(pJog);   // tira vida, empurra e desativa o sangue
}

void GerenciadorColisoes::removerInimigosMortos() {
    for (std::vector<Entidades::Personagens::Inimigo*>::iterator it = LIs.begin(); it != LIs.end();) {
        if (!(*it)->estaAtiva()) {
            // Se for um Drácula, o sangue dele morre junto: tira da LPs antes
            // de a fase deletar (senão a LPs fica apontando para lixo).
            Entidades::Personagens::Dracula* pDrac = dynamic_cast<Entidades::Personagens::Dracula*>(*it);
            if (pDrac)
                LPs.erase(pDrac->getSangue());
            it = LIs.erase(it);
        } else {
            ++it;
        }
    }
}
void GerenciadorColisoes::colisaoObstaculoJog() {
    for(Entidades::Obstaculos::Obstaculo* pObs : LOs) {
        if(verificaColisao(pObs, pJog1)){
            pObs->obstacularizar(pJog1);
        }
            
        if(pJog2){
            if(verificaColisao(pObs, pJog2)){
                pObs->obstacularizar(pJog2);
            }
        }
    }
}

} // namespace Gerenciadores

