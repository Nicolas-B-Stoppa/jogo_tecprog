#pragma once

#include "Entidades/Personagens/Inimigo.hpp"

namespace Entidades::Personagens {

// <<Inimigo 1 - Fácil>>: voa em onda, ignora a gravidade.
class Morcego : public Inimigo {
private:
    float raio;          // amplitude do voo
    float origemY;
    float tempo;

    static constexpr float VELOCIDADE = 120.f;
    static constexpr float PATRULHA = 150.f;

protected:
    void salvarDataBuffer() override;

public:
    Morcego(sf::Vector2f posicao);
    ~Morcego();

    void executar() override;
    void mover() override;
    void danificar(Cacador* pJog) override;
};

} // namespace Entidades::Personagens
