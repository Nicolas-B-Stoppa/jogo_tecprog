#pragma once

#include "Fases/Fase.hpp"

namespace Fases {

class FasePrimeira : public Fase {
public:
    FasePrimeira(bool carregando = false);   // true: lê do save em vez de sortear
    ~FasePrimeira();
protected:
    void criarInimigos() override;
    void criarObstaculos() override;

    void criarVampiros();
    void criarGosmas();

    void carregarInimigos() override;
    void carregarObstaculos() override;
    void carregarVampiros();
    void carregarGosmas();
private:
    const int maxINIMMedios;
};

} // namespace Fases
