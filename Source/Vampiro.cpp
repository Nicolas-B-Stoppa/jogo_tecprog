#include "Entidades/Personagens/Inimigos/Vampiro.hpp"

namespace Entidades::Personagens {

Vampiro::Vampiro() {}

Vampiro::~Vampiro() {}

void Vampiro::danificar(Cacador* pcaca){
    if (!pcaca)
        return;

    (*this)++;
    if(esfomeado){
        (*this)++;
        (*pcaca)--;
    }
    (*pcaca)--;
}

} // namespace Entidades::Personagens
