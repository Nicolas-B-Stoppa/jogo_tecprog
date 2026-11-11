#pragma once

#include "Entidades/Entidade.hpp"

namespace Entidades::Personagens {

class Personagem : public Entidades::Entidade {
public:
    Personagem(sf::Vector2f posicao = {0.f, 0.f}, sf::Vector2f tamanho = {50.f, 50.f},
               int vidas = 3, float velocidade = 300.f);
    ~Personagem();
    void operator++(int);      // pós-fixado:  personagem++ (soma vida)
    void operator--(int);      // pós-fixado:  personagem-- (perde vida)
    bool estaAtiva() const override;   // ativo enquanto tiver vidas

    // Levou dano: empurra para longe de quem causou e fica invencível por um tempo.
    void sofrerKnockback(const Entidade* pCausador);
    bool estaInvencivel() const;
protected:
    int vidas;
    float velocidade;

    sf::Vector2f empurrao;     // velocidade do empurrão (o y vira o pulinho em velY)
    float tempoInvencivel;     // enquanto > 0, não leva dano

    static constexpr sf::Vector2f FORCA_EMPURRAO{400.f, 300.f};
    static constexpr float TEMPO_INVENCIVEL = 1.f;
    static constexpr float DURACAO_EMPURRAO = 0.3f;   // o empurrão são os primeiros 0,3 s da invencibilidade

    bool estaSendoEmpurrado() const;
    float atualizarKnockback();   // desconta o tempo e empurra; devolve quanto andou em x

    virtual void executar() = 0;
    virtual void salvar() = 0;
    virtual void mover() = 0;
};

} // namespace Entidades::Personagens
