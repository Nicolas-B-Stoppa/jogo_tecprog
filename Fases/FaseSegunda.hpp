#pragma once

#include "Fases/Fase.hpp"

namespace Fases {

class FaseSegunda : public Fase {
public:
    FaseSegunda();
    ~FaseSegunda();
protected:
    void criarDracula();
    void criarPlataforma();
    void criarSangue();
private:
    const int maxChefoes;
};

} // namespace Fases
