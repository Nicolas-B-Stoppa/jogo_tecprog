#pragma once

#include "Entidades/Personagens/Inimigos/Inimigo.hpp"
#include "Entidades/Personagens/Cacador.hpp"

namespace Entidades::Personagens {

class Vampiro : public Inimigo {
public:
    Vampiro();
    ~Vampiro();
protected:
    bool esfomeado;
    void danificar(Cacador* pcaca)override;
};

} // namespace Entidades::Personagens
