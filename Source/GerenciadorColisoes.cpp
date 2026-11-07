#include "Gerenciadores/GerenciadorColisoes.hpp"

#include "Entidades/Entidade.hpp"
#include "Entidades/Personagens/Cacador.hpp"
#include "Entidades/Personagens/Inimigos/Inimigo.hpp"
#include "Entidades/Obstaculos/Obstaculo.hpp"

namespace Gerenciadores {

GerenciadorColisoes::GerenciadorColisoes() : pJog1(nullptr), pJog2(nullptr) {}

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

bool GerenciadorColisoes::verificaColisao(Entidades::Entidade* pEnt1, Entidades::Entidade* pEnt2) const{

    if (!pEnt1 || !pEnt2)
        return false;

    sf::FloatRect r1(pEnt1->getPosicao(), pEnt1->getTamanho());
    sf::FloatRect r2(pEnt2->getPosicao(), pEnt2->getTamanho());
    return r1.findIntersection(r2).has_value();


}

void GerenciadorColisoes::executar() {
    colisaoInimigoJog();
    // TODO: descomentar quando estiverem implementados
    // colisaoObstaculoJog();
    // colisaoProjetilJog();
}

void GerenciadorColisoes::colisaoInimigoJog() {

    for(Entidades::Personagens::Inimigo* pIni : LIs) {
        \
        if(verificaColisao(pIni, pJog1) && !pJog1->estaEmKnockback()){
            pIni->danificar(pJog1);   // o danificar já aplica o knockback
        }
            
        if(pJog2){
            if(verificaColisao(pIni, pJog2) && !pJog2->estaEmKnockback()){
                pIni->danificar(pJog2);
            }
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

} // namespace Gerenciadores

