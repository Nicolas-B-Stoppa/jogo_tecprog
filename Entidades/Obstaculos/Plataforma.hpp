#pragma once

#include "Entidades/Obstaculos/Obstaculo.hpp"
#include <fstream>

namespace Entidades::Obstaculos {

class Plataforma : public Obstaculo {
protected:
    float tempo;     // usado no sobe e desce
    float yOrigem;   // altura em que foi criada
    float empuxo;    // força para cima que anula a gravidade: a plataforma flutua

    void subirEDescer();
public:
    Plataforma(sf::Vector2f posicao);
    ~Plataforma();
    void executar() override;
    void salvar() override;
    void carregar(std::ifstream& arquivo);   // lê o resto da linha (depois de x y)
    void obstacularizar(Personagens::Cacador* pJog) override;
};

} // namespace Entidades::Obstaculos
