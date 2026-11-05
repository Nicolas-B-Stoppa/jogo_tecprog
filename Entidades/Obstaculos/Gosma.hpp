#pragma once

#include "Entidades/Obstaculos/Obstaculo.hpp"

namespace Entidades::Obstaculos {

class Gosma : public Obstaculo {
public:
    Gosma();
    ~Gosma();
protected:
    float slow;

};

} // namespace Entidades::Obstaculos
