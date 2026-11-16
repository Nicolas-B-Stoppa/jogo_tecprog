#pragma once

#include "Entidades/Obstaculos/Obstaculo.hpp"

namespace Entidades::Obstaculos {

class Estaca : public Obstaculo {
protected:
    int durabilidade;   // toques que a estaca aguenta antes de quebrar
public:
    Estaca(sf::Vector2f posicao);
    ~Estaca();
    void executar() override;
    void salvar() override;
    void obstacularizar(Personagens::Cacador* pJog) override;
    bool estaAtiva() const override;   // false: quebrou (durabilidade chegou a 0)
};

} // namespace Entidades::Obstaculos
