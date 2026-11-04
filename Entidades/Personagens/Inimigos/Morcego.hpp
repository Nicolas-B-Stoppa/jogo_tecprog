#pragma once

#include "Entidades/Personagens/Inimigos/Inimigo.hpp"

namespace Entidades::Personagens {

class Morcego : public Inimigo {
public:
    Morcego();
    ~Morcego();
protected:
    bool vampiro;
    void danificar(Cacador* pcaca)override;
};

} // namespace Entidades::Personagens
