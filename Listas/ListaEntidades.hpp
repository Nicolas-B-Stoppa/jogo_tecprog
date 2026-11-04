#pragma once

#include "Listas/Lista.hpp"

namespace Entidades { class Entidade; }

namespace Listas {

// <<Coleção>>: dona das entidades de uma fase (deleta-as no fim).
class ListaEntidades {
private:
    Lista<Entidades::Entidade> LEs;

public:
    ListaEntidades();
    ~ListaEntidades();

    void incluir(Entidades::Entidade* pE);
    void percorrer();   // executa e desenha todas as entidades ativas
    void limpar();      // deleta as entidades e esvazia a lista
};

} // namespace Listas
