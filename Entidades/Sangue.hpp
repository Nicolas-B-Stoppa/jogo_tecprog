#pragma once

#include "Entidades/Entidade.hpp"

namespace Entidades {

class Sangue : public Entidade {
public:
    Sangue();
    ~Sangue();
    void executar();
    void salvar();
protected:
    bool ativo;
};

} // namespace Entidades
