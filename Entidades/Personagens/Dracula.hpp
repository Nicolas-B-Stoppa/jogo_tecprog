#pragma once

#include "Entidades/Personagens/Inimigo.hpp"

namespace Fases { class Fase; }

namespace Entidades::Personagens {

// <<Inimigo 3 - Chefão>>: arremessa sangue (Projetil) no caçador.
class Dracula : public Inimigo {
private:
    short int forca;
    float tempoTiro;
    Fases::Fase* pFase;   // quem cria os projéteis

    static constexpr float VELOCIDADE = 70.f;
    static constexpr float INTERVALO_TIRO = 2.f;
    static constexpr float ALCANCE = 500.f;
    static constexpr float DISTANCIA_MINIMA = 150.f;

    void arremessarSangue();

protected:
    void salvarDataBuffer() override;

public:
    Dracula(sf::Vector2f posicao, Fases::Fase* pFase);
    ~Dracula();

    void executar() override;
    void mover() override;
    void danificar(Cacador* pJog) override;
};

} // namespace Entidades::Personagens
