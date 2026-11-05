#pragma once

#include "Entidades/Obstaculos/Obstaculo.hpp"

namespace Entidades::Obstaculos {

class Estaca : public Obstaculo {
public:
    Estaca();
    ~Estaca();
protected:
    int dano;
    
};

} // namespace Entidades::Obstaculos
