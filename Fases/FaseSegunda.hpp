#pragma once

#include "Fases/Fase.hpp"

namespace Fases {

class FaseSegunda : public Fase {
public:
    FaseSegunda();
    ~FaseSegunda();
protected:
    void criarInimigos() override;
    void criarObstaculos() override;

    void criarDraculas();
    void criarPlataforma();
private:
    const int maxChefoes;
};

} // namespace Fases
