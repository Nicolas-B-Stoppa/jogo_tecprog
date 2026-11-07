#pragma once

#include "Entidades/Obstaculos/Obstaculo.hpp"

namespace Entidades::Obstaculos {

class Estaca : public Obstaculo {
public:
    Estaca();
    ~Estaca();
    void executar() override;
    void salvar() override;
    void obstacularizar(*Cacador pJog) override;
protected:
    bool danoso;
    
};

} // namespace Entidades::Obstaculos
