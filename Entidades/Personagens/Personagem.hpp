#pragma once

#include "Entidades/Entidade.hpp"

namespace Entidades::Personagens {

// <<Entidade - Abstrata>> Personagem: tem vidas, gravidade e se move.
class Personagem : public Entidade {
protected:
    int num_vidas;
    bool noChao;
    float fatorVelocidade;     // < 1 quando está na Gosma
    float tempoInvulneravel;   // evita perder várias vidas no mesmo toque

    static constexpr float TEMPO_INVULNERAVEL = 1.f;

    void aplicarGravidade();
    void atualizarTemporizadores();
    void salvarDataBuffer() override;

public:
    Personagem(sf::Vector2f posicao, sf::Vector2f tamanho, int vidas);
    virtual ~Personagem();

    virtual void executar() = 0;
    virtual void mover() = 0;
    void desenhar() override;   // pisca enquanto invulnerável

    void receberDano(int dano = 1);
    bool estaVivo() const;
    int getVidas() const;

    void setNoChao(bool n);
    bool getNoChao() const;
    void setFatorVelocidade(float f);
};

} // namespace Entidades::Personagens
