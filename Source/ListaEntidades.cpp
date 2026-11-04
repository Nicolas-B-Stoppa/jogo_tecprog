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

void ListaEntidades::percorrer() {
    for (auto* e = LEs.getPrimeiro(); e != nullptr; e = e->getProximo()) {
        Entidades::Entidade* pE = e->getInfo();
        if (pE->getAtivo()) {
            pE->executar();
            pE->desenhar();
        }
    }
}

void ListaEntidades::limpar() {
    for (auto* e = LEs.getPrimeiro(); e != nullptr; e = e->getProximo())
        delete e->getInfo();
    LEs.limpar();
}

} // namespace Listas
