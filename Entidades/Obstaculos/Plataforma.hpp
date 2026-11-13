#pragma once

#include "Entidades/Obstaculos/Obstaculo.hpp"

namespace Entidades::Obstaculos {

class Plataforma : public Obstaculo {
public:
    Plataforma(sf::Vector2f posicao);
    ~Plataforma();
    void executar() override;
    void salvar() override;
    void obstacularizar(Personagens::Cacador* pJog) override;
};

} // namespace Entidades::Obstaculos
