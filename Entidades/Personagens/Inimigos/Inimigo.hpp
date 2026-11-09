#pragma once

#include "Entidades/Personagens/Personagem.hpp"

namespace Entidades::Personagens {

class Cacador;   // declaração antecipada: basta para usar Cacador*

class Inimigo : public Personagem {
public:
    Inimigo(sf::Vector2f posicao = {0.f, 0.f}, sf::Vector2f tamanho = {50.f, 50.f},
            int vidas = 1, float velocidade = 150.f, float raio = 100.f);
    ~Inimigo();

    void executar() override;
    void salvar() override;
    virtual void danificar(Cacador* pcaca)=0;

    // Golpe da espada do caçador: perde uma vida e é empurrado para longe dele.
    void sofrerGolpe(const Entidade* pCausador);
    bool podeSofrerGolpe() const;   // false logo depois de levar um golpe
protected:
    int maldade;
    float angulo;              // avança com o tempo e gera o movimento periódico
    float raio;                // o quanto o inimigo se afasta da origem
    sf::Vector2f origem;       // ponto em torno do qual ele oscila

    float velKnockback;        // velocidade horizontal do empurrão
    float tempoKnockback;      // quanto tempo ainda falta de empurrão (s)
    float tempoInvulneravel;   // enquanto > 0, não leva outro golpe

    static constexpr float FORCA_KNOCKBACK_X = 400.f;
    static constexpr float FORCA_KNOCKBACK_Y = 300.f;   // pulinho para cima
    static constexpr float DURACAO_KNOCKBACK = 0.3f;
    static constexpr float DURACAO_INVULNERAVEL = 0.5f; // maior que o golpe (0,4 s): um golpe = um dano

    void atualizarKnockback();

    void avancarAngulo();
    void mover() override;     // padrão: vai-e-vem horizontal
};

} // namespace Entidades::Personagens
