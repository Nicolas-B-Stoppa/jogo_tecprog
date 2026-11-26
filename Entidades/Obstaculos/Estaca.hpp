#pragma once

#include "Entidades/Obstaculos/Obstaculo.hpp"
#include <fstream>

namespace Entidades::Obstaculos {

class Estaca : public Obstaculo {
protected:
    int durabilidade;   // toques que a estaca aguenta antes de quebrar
    bool quebrada;      // true: a fase tira a estaca do jogo

    void quebrar();     // marca como quebrada quando a durabilidade chega a 0
public:
    Estaca(sf::Vector2f posicao);
    ~Estaca();
    void executar() override;
    void salvar() override;
    void carregar(std::ifstream& arquivo);   // lê o resto da linha (depois de x y)
    void obstacularizar(Personagens::Cacador* pJog) override;
    bool estaAtiva() const override;   // false: quebrou
};

} // namespace Entidades::Obstaculos
