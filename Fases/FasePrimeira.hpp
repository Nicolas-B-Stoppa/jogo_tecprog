#pragma once

#include "Fases/Fase.hpp"

namespace Fases {

class FasePrimeira : public Fase {
public:
    FasePrimeira();
    ~FasePrimeira();
protected:
    void criarInimigos() override;
    void criarObstaculos() override;

    void criarMorcegos();
    void criarVampiros();
private:
    const int maxINIMMedios;
};

} // namespace Fases
