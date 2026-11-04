#include "Entidades/Personagens/Inimigos/Morcego.hpp"

#include "Entidades/Personagens/Cacador.hpp"

namespace Entidades::Personagens {

Morcego::Morcego() {}

Morcego::~Morcego() {}

void Morcego::danificar(Cacador* pcaca) {
    if (!pcaca)
        return;

    if(vampiro)
        (*this)++;
    (*pcaca)--;
}

} // namespace Entidades::Personagens
