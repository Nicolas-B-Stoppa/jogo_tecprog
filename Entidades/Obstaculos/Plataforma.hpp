#pragma once

#include "Entidades/Obstaculos/Obstaculo.hpp"

namespace Entidades::Obstaculos {

class Plataforma : public Obstaculo {
public:
    Plataforma();
    ~Plataforma();
    void executar() override;
    void salvar() override;
    void obstacularizar(*Cacador pJog) override;
protected:
    bool danoso;
};

} // namespace Entidades::Obstaculos
