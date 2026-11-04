#pragma once

#include "Fases/Fase.hpp"

namespace Fases {

// <<Fase 1>>: Morcegos + Vampiros, Plataformas + Gosmas.
class FasePrimeira : public Fase {
private:
    const int maxInimMedios;

    void criarInimMedios();
    void criarObstMedios();

protected:
    void criarInimigos() override;
    void criarObstaculos() override;

public:
    FasePrimeira(Entidades::Personagens::Cacador* j1, Entidades::Personagens::Cacador* j2 = nullptr);
    ~FasePrimeira();
};

} // namespace Fases
