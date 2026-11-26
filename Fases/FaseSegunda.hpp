#pragma once

#include "Fases/Fase.hpp"

namespace Fases {

class FaseSegunda : public Fase {
public:
    FaseSegunda(bool carregando = false);   // true: lê do save em vez de sortear
    ~FaseSegunda();
protected:
    void criarInimigos() override;
    void criarObstaculos() override;

    void criarDraculas();
    void criarEstacas();

    void carregarInimigos() override;
    void carregarObstaculos() override;
    void carregarDraculas();
    void carregarEstacas();
private:
    const int maxChefoes;
};

} // namespace Fases
