#pragma once

#include "Entidades/Obstaculos/Obstaculo.hpp"

namespace Entidades::Obstaculos {

// <<Obstáculo 1 - Fácil>>: plataforma sólida que flutua.
class Plataforma : public Obstaculo {
private:
    // Fração da gravidade anulada (1 = parada no ar, < 1 = afunda devagar).
    float flutuabilidade;

protected:
    void salvarDataBuffer() override;

public:
    Plataforma(sf::Vector2f posicao, sf::Vector2f tamanho = {100.f, 30.f}, float flutuabilidade = 1.f);
    ~Plataforma();

    void executar() override;
    void obstaculizar(Personagens::Personagem* p) override;
};

} // namespace Entidades::Obstaculos
