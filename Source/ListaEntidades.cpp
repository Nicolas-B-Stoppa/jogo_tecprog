#include "Listas/ListaEntidades.hpp"

#include "Entidades/Entidade.hpp"

namespace Listas {

ListaEntidades::ListaEntidades() {}

ListaEntidades::~ListaEntidades() {
    limpar();
}

void ListaEntidades::incluir(Entidades::Entidade* pE) {
    LEs.incluir(pE);
}

bool ListaEntidades::remover(Entidades::Entidade* pE) {
    return LEs.remover(pE);
}

void ListaEntidades::limpar() {
    // Primeiro deleta as entidades, depois os nós da lista.
    Lista<Entidades::Entidade>::Elemento<Entidades::Entidade>* pAtual = LEs.getPrimeiro();
    while (pAtual) {
        delete pAtual->getInfo();
        pAtual = pAtual->getProx();
    }
    LEs.limpar();
}

void ListaEntidades::removerInativas() {
    Lista<Entidades::Entidade>::Elemento<Entidades::Entidade>* pAtual = LEs.getPrimeiro();
    while (pAtual) {
        // Guarda o próximo antes, porque o remover apaga o nó atual.
        Lista<Entidades::Entidade>::Elemento<Entidades::Entidade>* pProximo = pAtual->getProx();
        Entidades::Entidade* pE = pAtual->getInfo();
        if (pE && !pE->estaAtiva()) {
            LEs.remover(pE);
            delete pE;
        }
        pAtual = pProximo;
    }
}

void ListaEntidades::executar() {
    Lista<Entidades::Entidade>::Elemento<Entidades::Entidade>* pAtual = LEs.getPrimeiro();
    while (pAtual) {
        pAtual->getInfo()->executar();
        pAtual = pAtual->getProx();
    }
}

void ListaEntidades::desenhar(sf::RenderWindow& janela) {
    Lista<Entidades::Entidade>::Elemento<Entidades::Entidade>* pAtual = LEs.getPrimeiro();
    while (pAtual) {
        pAtual->getInfo()->desenhar(janela);
        pAtual = pAtual->getProx();
    }
}

Entidades::Entidade* ListaEntidades::operator[](int pos) const {
    return LEs[pos];
}

int ListaEntidades::getTamanho() const {
    return LEs.getTamanho();
}

} // namespace Listas
