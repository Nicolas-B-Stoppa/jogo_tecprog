#pragma once

#include "Entidades/Obstaculos/Obstaculo.hpp"

namespace Entidades::Obstaculos {

// <<Obstáculo 2 - Médio>>: deixa quem pisa mais lento.
class Gosma : public Obstaculo {
private:
    float viscosidade;   // multiplicador de velocidade (0..1)

protected:
    void salvarDataBuffer() override;

public:
    Gosma(sf::Vector2f posicao, sf::Vector2f tamanho = {120.f, 15.f});
    ~Gosma();

    void obstaculizar(Personagens::Personagem* p) override;
};

} // namespace Entidades::Obstaculos
