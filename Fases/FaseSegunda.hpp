#pragma once

#include "Fases/Fase.hpp"

namespace Fases {

// <<Fase 2>>: Morcegos + Drácula, Plataformas + Estacas.
class FaseSegunda : public Fase {
private:
    const int maxChefes;

    void criarChefes();
    void criarObstDificeis();

protected:
    void criarInimigos() override;
    void criarObstaculos() override;

public:
    FaseSegunda(Entidades::Personagens::Cacador* j1, Entidades::Personagens::Cacador* j2 = nullptr);
    ~FaseSegunda();

    void criarProjetil(sf::Vector2f posicao, float direcao) override;
};

} // namespace Fases
