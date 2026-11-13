#pragma once

#include "Entidades/Obstaculos/Obstaculo.hpp"

namespace Entidades::Obstaculos {

class Estaca : public Obstaculo {
public:
    Estaca(sf::Vector2f posicao);
    ~Estaca();
    void executar() override;
    void salvar() override;
    void obstacularizar(Personagens::Cacador* pJog) override;
};

} // namespace Entidades::Obstaculos
