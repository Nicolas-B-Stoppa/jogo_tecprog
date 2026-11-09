#pragma once

#include "Entidades/Personagens/Personagem.hpp"

namespace Entidades::Personagens {

class Cacador : public Personagem {
public:
    Cacador(sf::Vector2f posicao = {100.f, 300.f});
    ~Cacador();

    void executar() override;
    void salvar() override;

    void sofrerKnockback(const Entidade* pCausador);   // empurra para longe de quem causou o dano
    bool estaEmKnockback() const;
    bool estaArmado() const;                           // atacando com a espada
protected:
    enum class Animacao { Parado, Andando, Pulando, Atacando };

    // Uma folha de sprites por animação
    sf::Texture texParado;
    sf::Texture texAndar;
    sf::Texture texPular;
    sf::Texture texAtaque;
    Animacao animAtual;

    bool armado;               // true enquanto o golpe de espada está acontecendo
    bool andando;              // apertou A ou D neste frame
    float velKnockback;        // velocidade horizontal do empurrão
    float tempoKnockback;      // quanto tempo ainda falta de empurrão (s)

    static constexpr float FORCA_PULO = 650.f;
    static constexpr float FORCA_KNOCKBACK_X = 450.f;
    static constexpr float FORCA_KNOCKBACK_Y = 350.f;   // pulinho para cima
    static constexpr float DURACAO_KNOCKBACK = 0.3f;

    static constexpr float ESCALA_SPRITE = 1.1f;    // o corpo tem ~64px de altura no quadro de 128px
    static constexpr float ORIGEM_X_SPRITE = 33.f;  // centro do corpo dentro do quadro

    void mover() override;
    void escolherAnimacao();
    void trocarAnimacao(Animacao nova);
};

} // namespace Entidades::Personagens
