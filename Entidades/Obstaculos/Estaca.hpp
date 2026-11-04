#pragma once

#include "Entidades/Obstaculos/Obstaculo.hpp"

namespace Entidades::Obstaculos {

// <<Obstáculo 3 - Difícil>>: estacas que machucam.
class Estaca : public Obstaculo {
private:
    short int danosidade;

protected:
    void salvarDataBuffer() override;

public:
    Estaca(sf::Vector2f posicao, sf::Vector2f tamanho = {50.f, 30.f});
    ~Estaca();

    void obstaculizar(Personagens::Personagem* p) override;
};

} // namespace Entidades::Obstaculos
