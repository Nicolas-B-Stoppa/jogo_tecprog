#pragma once

#include "Entidades/Entidade.hpp"

namespace Entidades::Obstaculos {

class Obstaculo : public Entidades::Entidade {
public:
    Obstaculo();
    ~Obstaculo();
    virtual void executar() = 0;
    virtual void obstacularizar(p *Cacador) = 0;
};

} // namespace Entidades::Obstaculos
