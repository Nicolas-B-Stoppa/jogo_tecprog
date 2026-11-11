#pragma once

#include "Entidades/Obstaculos/Obstaculo.hpp"

namespace Entidades::Obstaculos {

class Gosma : public Obstaculo {
public:
    Gosma();
    ~Gosma();
    void executar() override;
    void salvar() override;
    void obstacularizar(Personagens::Cacador* pJog) override;
protected:
    bool danoso;

};

} // namespace Entidades::Obstaculos
