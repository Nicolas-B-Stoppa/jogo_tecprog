#pragma once

#include "Entidades/Obstaculos/Obstaculo.hpp"

namespace Entidades::Obstaculos {

class Estaca : public Obstaculo {
public:
    Estaca();
    ~Estaca();
protected:
    int dano; //qantia reduzida da vida do jogador ao encostar na estaca.
    
};

} // namespace Entidades::Obstaculos
