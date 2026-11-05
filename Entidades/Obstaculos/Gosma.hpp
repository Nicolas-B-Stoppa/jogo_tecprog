#pragma once

#include "Entidades/Obstaculos/Obstaculo.hpp"

namespace Entidades::Obstaculos {

class Gosma : public Obstaculo {
public:
    Gosma();
    ~Gosma();
protected:
    float slow; //quantidade reduzida da velocidade do caçador ao passar pela gosma.

};

} // namespace Entidades::Obstaculos
