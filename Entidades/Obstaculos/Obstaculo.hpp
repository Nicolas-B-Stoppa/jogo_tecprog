#pragma once

#include "Entidades/Entidade.hpp"

namespace Entidades::Personagens { class Cacador; }   // declaração antecipada

namespace Entidades::Obstaculos {

class Obstaculo : public Entidades::Entidade {
public:
    Obstaculo();
    ~Obstaculo();
    virtual void executar() = 0;
    virtual void salvar() = 0;
    virtual void obstacularizar(Personagens::Cacador* pJog) = 0;
protected:
    bool danoso;
};

} // namespace Entidades::Obstaculos
