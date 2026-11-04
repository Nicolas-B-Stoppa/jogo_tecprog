#pragma once

#include "Entidades/Personagens/Inimigo.hpp"

namespace Entidades::Personagens {

// <<Inimigo 2 - Médio>>: anda pelo chão e persegue o caçador quando perto.
class Vampiro : public Inimigo {
private:
    int forcaMordida;

    static constexpr float VELOCIDADE = 100.f;
    static constexpr float RAIO_VISAO = 300.f;
    static constexpr float PATRULHA = 150.f;

protected:
    void salvarDataBuffer() override;

public:
    Vampiro(sf::Vector2f posicao);
    ~Vampiro();

    void executar() override;
    void mover() override;
    void danificar(Cacador* pJog) override;
};

} // namespace Entidades::Personagens
