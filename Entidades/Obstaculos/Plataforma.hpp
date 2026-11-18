#pragma once

#include "Entidades/Obstaculos/Obstaculo.hpp"

namespace Entidades::Obstaculos {

class Plataforma : public Obstaculo {
protected:
    bool movel;      // 40% de chance de ser true: a plataforma sobe e desce
    float tempo;     // usado no sobe e desce
    float yOrigem;   // altura em que foi criada
    float empuxo;    // força para cima que anula a gravidade: a plataforma flutua

    void subirEDescer();
public:
    Plataforma(sf::Vector2f posicao);
    ~Plataforma();
    void executar() override;
    void salvar() override;
    void obstacularizar(Personagens::Cacador* pJog) override;
};

} // namespace Entidades::Obstaculos
