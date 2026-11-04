#pragma once

#include "Entidades/Entidade.hpp"

namespace Entidades {

namespace Personagens { class Cacador; }

// <<Entidade>> Projetil: gota de sangue arremessada pelo Drácula.
class Sangue : public Entidade {
private:
    float tempoVida;
    int dano;

    static constexpr float VELOCIDADE = 400.f;
    static constexpr float DURACAO = 3.f;
    static constexpr float EMPUXO = 0.8f;   // contrabalança parte da gravidade

protected:
    void salvarDataBuffer() override;

public:
    Sangue(sf::Vector2f posicao, float direcao);
    ~Sangue();

    void executar() override;
    void danificar(Personagens::Cacador* pJog);
};

} // namespace Entidades
